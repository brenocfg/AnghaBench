#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct nouveau_mxm {int dummy; } ;
struct nouveau_bios {int* data; } ;
struct TYPE_2__ {int outp_type; int conn_type; int /*<<< orphan*/  dig_conn; int /*<<< orphan*/  ddc_port; } ;
struct context {int* outp; TYPE_1__ desc; } ;

/* Variables and functions */
 int DCB_CONNECTOR_DVI_D ; 
 int DCB_CONNECTOR_HDMI_1 ; 
 int DCB_CONNECTOR_eDP ; 
 int DCB_OUTPUT_DP ; 
 int /*<<< orphan*/  dcb_conn (struct nouveau_bios*,int,int*,int*) ; 
 int mxm_ddc_map (struct nouveau_bios*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxm_match_dcb ; 
 int mxm_sor_map (struct nouveau_bios*,int /*<<< orphan*/ ) ; 
 scalar_t__ mxms_foreach (struct nouveau_mxm*,int,int /*<<< orphan*/ ,struct context*) ; 
 int mxms_version (struct nouveau_mxm*) ; 
 struct nouveau_mxm* nouveau_mxm (struct nouveau_bios*) ; 
 int /*<<< orphan*/  nv_debug (struct nouveau_mxm*,char*,int,int,int) ; 

__attribute__((used)) static int
mxm_dcb_sanitise_entry(struct nouveau_bios *bios, void *data, int idx, u16 pdcb)
{
	struct nouveau_mxm *mxm = nouveau_mxm(bios);
	struct context ctx = { .outp = (u32 *)(bios->data + pdcb) };
	u8 type, i2cidx, link, ver, len;
	u8 *conn;

	/* look for an output device structure that matches this dcb entry.
	 * if one isn't found, disable it.
	 */
	if (mxms_foreach(mxm, 0x01, mxm_match_dcb, &ctx)) {
		nv_debug(mxm, "disable %d: 0x%08x 0x%08x\n",
			idx, ctx.outp[0], ctx.outp[1]);
		ctx.outp[0] |= 0x0000000f;
		return 0;
	}

	/* modify the output's ddc/aux port, there's a pointer to a table
	 * with the mapping from mxm ddc/aux port to dcb i2c_index in the
	 * vbios mxm table
	 */
	i2cidx = mxm_ddc_map(bios, ctx.desc.ddc_port);
	if ((ctx.outp[0] & 0x0000000f) != DCB_OUTPUT_DP)
		i2cidx = (i2cidx & 0x0f) << 4;
	else
		i2cidx = (i2cidx & 0xf0);

	if (i2cidx != 0xf0) {
		ctx.outp[0] &= ~0x000000f0;
		ctx.outp[0] |= i2cidx;
	}

	/* override dcb sorconf.link, based on what mxm data says */
	switch (ctx.desc.outp_type) {
	case 0x00: /* Analog CRT */
	case 0x01: /* Analog TV/HDTV */
		break;
	default:
		link = mxm_sor_map(bios, ctx.desc.dig_conn) & 0x30;
		ctx.outp[1] &= ~0x00000030;
		ctx.outp[1] |= link;
		break;
	}

	/* we may need to fixup various other vbios tables based on what
	 * the descriptor says the connector type should be.
	 *
	 * in a lot of cases, the vbios tables will claim DVI-I is possible,
	 * and the mxm data says the connector is really HDMI.  another
	 * common example is DP->eDP.
	 */
	conn  = bios->data;
	conn += dcb_conn(bios, (ctx.outp[0] & 0x0000f000) >> 12, &ver, &len);
	type  = conn[0];
	switch (ctx.desc.conn_type) {
	case 0x01: /* LVDS */
		ctx.outp[1] |= 0x00000004; /* use_power_scripts */
		/* XXX: modify default link width in LVDS table */
		break;
	case 0x02: /* HDMI */
		type = DCB_CONNECTOR_HDMI_1;
		break;
	case 0x03: /* DVI-D */
		type = DCB_CONNECTOR_DVI_D;
		break;
	case 0x0e: /* eDP, falls through to DPint */
		ctx.outp[1] |= 0x00010000;
	case 0x07: /* DP internal, wtf is this?? HP8670w */
		ctx.outp[1] |= 0x00000004; /* use_power_scripts? */
		type = DCB_CONNECTOR_eDP;
		break;
	default:
		break;
	}

	if (mxms_version(mxm) >= 0x0300)
		conn[0] = type;

	return 0;
}
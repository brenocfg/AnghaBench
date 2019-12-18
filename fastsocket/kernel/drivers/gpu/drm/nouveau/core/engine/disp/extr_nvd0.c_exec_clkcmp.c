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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct nvbios_outp {int dummy; } ;
struct nvbios_ocfg {int /*<<< orphan*/ * clkcmp; } ;
struct nvbios_init {int offset; int crtc; int execute; struct dcb_output* outp; struct nouveau_bios* bios; int /*<<< orphan*/  subdev; } ;
struct TYPE_2__ {int lvdsconf; } ;
struct nv50_disp_priv {TYPE_1__ sor; } ;
struct nouveau_bios {int dummy; } ;
struct dcb_output {int type; } ;

/* Variables and functions */
#define  DCB_OUTPUT_ANALOG 131 
#define  DCB_OUTPUT_DP 130 
#define  DCB_OUTPUT_LVDS 129 
#define  DCB_OUTPUT_TMDS 128 
 int exec_lookup (struct nv50_disp_priv*,int,int,int,struct dcb_output*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nvbios_outp*) ; 
 struct nouveau_bios* nouveau_bios (struct nv50_disp_priv*) ; 
 int nv_rd32 (struct nv50_disp_priv*,int) ; 
 int /*<<< orphan*/  nv_subdev (struct nv50_disp_priv*) ; 
 int /*<<< orphan*/  nvbios_exec (struct nvbios_init*) ; 
 int nvbios_ocfg_match (struct nouveau_bios*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nvbios_ocfg*) ; 
 int nvbios_oclk_match (struct nouveau_bios*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32
exec_clkcmp(struct nv50_disp_priv *priv, int head, int id,
	    u32 pclk, struct dcb_output *dcb)
{
	struct nouveau_bios *bios = nouveau_bios(priv);
	struct nvbios_outp info1;
	struct nvbios_ocfg info2;
	u8  ver, hdr, cnt, len;
	u32 ctrl = 0x00000000;
	u32 data, conf = ~0;
	int outp;

	for (outp = 0; !(ctrl & (1 << head)) && outp < 8; outp++) {
		ctrl = nv_rd32(priv, 0x660180 + (outp * 0x20));
		if (ctrl & (1 << head))
			break;
	}

	if (outp == 8)
		return false;

	data = exec_lookup(priv, head, outp, ctrl, dcb, &ver, &hdr, &cnt, &len, &info1);
	if (data == 0x0000)
		return conf;

	switch (dcb->type) {
	case DCB_OUTPUT_TMDS:
		conf = (ctrl & 0x00000f00) >> 8;
		if (pclk >= 165000)
			conf |= 0x0100;
		break;
	case DCB_OUTPUT_LVDS:
		conf = priv->sor.lvdsconf;
		break;
	case DCB_OUTPUT_DP:
		conf = (ctrl & 0x00000f00) >> 8;
		break;
	case DCB_OUTPUT_ANALOG:
	default:
		conf = 0x00ff;
		break;
	}

	data = nvbios_ocfg_match(bios, data, conf, &ver, &hdr, &cnt, &len, &info2);
	if (data && id < 0xff) {
		data = nvbios_oclk_match(bios, info2.clkcmp[id], pclk);
		if (data) {
			struct nvbios_init init = {
				.subdev = nv_subdev(priv),
				.bios = bios,
				.offset = data,
				.outp = dcb,
				.crtc = head,
				.execute = 1,
			};

			nvbios_exec(&init);
		}
	}

	return conf;
}
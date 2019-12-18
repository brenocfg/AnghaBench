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
struct nouveau_mxm {int dummy; } ;
struct TYPE_2__ {scalar_t__ debug; } ;

/* Variables and functions */
 scalar_t__ NV_DBG_DEBUG ; 
 int ROM32 (int) ; 
 int* mxms_data (struct nouveau_mxm*) ; 
 int mxms_headerlen (struct nouveau_mxm*) ; 
 int mxms_structlen (struct nouveau_mxm*) ; 
 int mxms_version (struct nouveau_mxm*) ; 
 int /*<<< orphan*/  nv_debug (struct nouveau_mxm*,char*,...) ; 
 TYPE_1__* nv_subdev (struct nouveau_mxm*) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 

bool
mxms_foreach(struct nouveau_mxm *mxm, u8 types,
	     bool (*exec)(struct nouveau_mxm *, u8 *, void *), void *info)
{
	u8 *mxms = mxms_data(mxm);
	u8 *desc = mxms + mxms_headerlen(mxm);
	u8 *fini = desc + mxms_structlen(mxm) - 1;
	while (desc < fini) {
		u8 type = desc[0] & 0x0f;
		u8 headerlen = 0;
		u8 recordlen = 0;
		u8 entries = 0;

		switch (type) {
		case 0: /* Output Device Structure */
			if (mxms_version(mxm) >= 0x0300)
				headerlen = 8;
			else
				headerlen = 6;
			break;
		case 1: /* System Cooling Capability Structure */
		case 2: /* Thermal Structure */
		case 3: /* Input Power Structure */
			headerlen = 4;
			break;
		case 4: /* GPIO Device Structure */
			headerlen = 4;
			recordlen = 2;
			entries   = (ROM32(desc[0]) & 0x01f00000) >> 20;
			break;
		case 5: /* Vendor Specific Structure */
			headerlen = 8;
			break;
		case 6: /* Backlight Control Structure */
			if (mxms_version(mxm) >= 0x0300) {
				headerlen = 4;
				recordlen = 8;
				entries   = (desc[1] & 0xf0) >> 4;
			} else {
				headerlen = 8;
			}
			break;
		case 7: /* Fan Control Structure */
			headerlen = 8;
			recordlen = 4;
			entries   = desc[1] & 0x07;
			break;
		default:
			nv_debug(mxm, "unknown descriptor type %d\n", type);
			return false;
		}

		if (nv_subdev(mxm)->debug >= NV_DBG_DEBUG && (exec == NULL)) {
			static const char * mxms_desc_name[] = {
				"ODS", "SCCS", "TS", "IPS",
				"GSD", "VSS", "BCS", "FCS",
			};
			u8 *dump = desc;
			int i, j;

			nv_debug(mxm, "%4s: ", mxms_desc_name[type]);
			for (j = headerlen - 1; j >= 0; j--)
				pr_cont("%02x", dump[j]);
			pr_cont("\n");
			dump += headerlen;

			for (i = 0; i < entries; i++, dump += recordlen) {
				nv_debug(mxm, "      ");
				for (j = recordlen - 1; j >= 0; j--)
					pr_cont("%02x", dump[j]);
				pr_cont("\n");
			}
		}

		if (types & (1 << type)) {
			if (!exec(mxm, desc, info))
				return false;
		}

		desc += headerlen + (entries * recordlen);
	}

	return true;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct nouveau_bios {int dummy; } ;

/* Variables and functions */
 int mxm_table (struct nouveau_bios*,int*,int*) ; 
 int nv_ro08 (struct nouveau_bios*,int) ; 
 int nv_ro16 (struct nouveau_bios*,int) ; 
 int /*<<< orphan*/  nv_warn (struct nouveau_bios*,char*,int) ; 

u8
mxm_ddc_map(struct nouveau_bios *bios, u8 port)
{
	u8  ver, hdr;
	u16 mxm = mxm_table(bios, &ver, &hdr);
	if (mxm && hdr >= 8) {
		u16 map = nv_ro16(bios, mxm + 6);
		if (map) {
			ver = nv_ro08(bios, map);
			if (ver == 0x10) {
				if (port < nv_ro08(bios, map + 3)) {
					map += nv_ro08(bios, map + 1);
					map += port;
					return nv_ro08(bios, map);
				}

				return 0x00;
			}

			nv_warn(bios, "unknown ddc map v%02x\n", ver);
		}
	}

	/* v2.x: directly write port as dcb i2cidx */
	return (port << 4) | port;
}
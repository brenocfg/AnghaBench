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
typedef  int u16 ;
struct TYPE_2__ {int chip; } ;
struct nouveau_bios {TYPE_1__ version; } ;

/* Variables and functions */
 int mxm_table (struct nouveau_bios*,int*,int*) ; 
 int* nv84_sor_map ; 
 int* nv92_sor_map ; 
 int* nv94_sor_map ; 
 int* nv98_sor_map ; 
 int nv_ro08 (struct nouveau_bios*,int) ; 
 int nv_ro16 (struct nouveau_bios*,int) ; 
 int /*<<< orphan*/  nv_warn (struct nouveau_bios*,char*,...) ; 

u8
mxm_sor_map(struct nouveau_bios *bios, u8 conn)
{
	u8  ver, hdr;
	u16 mxm = mxm_table(bios, &ver, &hdr);
	if (mxm && hdr >= 6) {
		u16 map = nv_ro16(bios, mxm + 4);
		if (map) {
			ver = nv_ro08(bios, map);
			if (ver == 0x10) {
				if (conn < nv_ro08(bios, map + 3)) {
					map += nv_ro08(bios, map + 1);
					map += conn;
					return nv_ro08(bios, map);
				}

				return 0x00;
			}

			nv_warn(bios, "unknown sor map v%02x\n", ver);
		}
	}

	if (bios->version.chip == 0x84 || bios->version.chip == 0x86)
		return nv84_sor_map[conn];
	if (bios->version.chip == 0x92)
		return nv92_sor_map[conn];
	if (bios->version.chip == 0x94 || bios->version.chip == 0x96)
		return nv94_sor_map[conn];
	if (bios->version.chip == 0x98)
		return nv98_sor_map[conn];

	nv_warn(bios, "missing sor map\n");
	return 0x00;
}
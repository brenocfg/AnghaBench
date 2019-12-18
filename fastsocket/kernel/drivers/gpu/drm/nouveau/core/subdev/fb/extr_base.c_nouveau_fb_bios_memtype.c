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
struct bit_entry {int version; int length; scalar_t__ offset; } ;

/* Variables and functions */
 int NV_MEM_TYPE_DDR2 ; 
 int NV_MEM_TYPE_DDR3 ; 
 int NV_MEM_TYPE_GDDR3 ; 
 int NV_MEM_TYPE_GDDR5 ; 
 int NV_MEM_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  bit_entry (struct nouveau_bios*,char,struct bit_entry*) ; 
 int nv_rd32 (struct nouveau_bios*,int) ; 
 int nv_ro08 (struct nouveau_bios*,int) ; 
 int nv_ro16 (struct nouveau_bios*,scalar_t__) ; 

int
nouveau_fb_bios_memtype(struct nouveau_bios *bios)
{
	struct bit_entry M;
	u8 ramcfg;

	ramcfg = (nv_rd32(bios, 0x101000) & 0x0000003c) >> 2;
	if (!bit_entry(bios, 'M', &M) && M.version == 2 && M.length >= 5) {
		u16 table   = nv_ro16(bios, M.offset + 3);
		u8  version = nv_ro08(bios, table + 0);
		u8  header  = nv_ro08(bios, table + 1);
		u8  record  = nv_ro08(bios, table + 2);
		u8  entries = nv_ro08(bios, table + 3);
		if (table && version == 0x10 && ramcfg < entries) {
			u16 entry = table + header + (ramcfg * record);
			switch (nv_ro08(bios, entry) & 0x0f) {
			case 0: return NV_MEM_TYPE_DDR2;
			case 1: return NV_MEM_TYPE_DDR3;
			case 2: return NV_MEM_TYPE_GDDR3;
			case 3: return NV_MEM_TYPE_GDDR5;
			default:
				break;
			}

		}
	}

	return NV_MEM_TYPE_UNKNOWN;
}
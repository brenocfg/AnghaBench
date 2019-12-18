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
struct nvbios_init {struct nouveau_bios* bios; } ;
struct nouveau_bios {int dummy; } ;

/* Variables and functions */
 int init_io_flag_condition_table (struct nvbios_init*) ; 
 int init_rdvgai (struct nvbios_init*,int,int) ; 
 int nv_ro08 (struct nouveau_bios*,int) ; 
 int nv_ro16 (struct nouveau_bios*,int) ; 

__attribute__((used)) static bool
init_io_flag_condition_met(struct nvbios_init *init, u8 cond)
{
	struct nouveau_bios *bios = init->bios;
	u16 table = init_io_flag_condition_table(init);
	if (table) {
		u16 port = nv_ro16(bios, table + (cond * 9) + 0);
		u8 index = nv_ro08(bios, table + (cond * 9) + 2);
		u8  mask = nv_ro08(bios, table + (cond * 9) + 3);
		u8 shift = nv_ro08(bios, table + (cond * 9) + 4);
		u16 data = nv_ro16(bios, table + (cond * 9) + 5);
		u8 dmask = nv_ro08(bios, table + (cond * 9) + 7);
		u8 value = nv_ro08(bios, table + (cond * 9) + 8);
		u8 ioval = (init_rdvgai(init, port, index) & mask) >> shift;
		return (nv_ro08(bios, data + ioval) & dmask) == value;
	}
	return false;
}
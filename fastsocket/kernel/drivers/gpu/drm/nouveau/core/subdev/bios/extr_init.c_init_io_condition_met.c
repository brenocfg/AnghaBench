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
typedef  scalar_t__ u16 ;
struct nvbios_init {struct nouveau_bios* bios; } ;
struct nouveau_bios {int dummy; } ;

/* Variables and functions */
 scalar_t__ init_io_condition_table (struct nvbios_init*) ; 
 int init_rdvgai (struct nvbios_init*,scalar_t__,int) ; 
 int nv_ro08 (struct nouveau_bios*,scalar_t__) ; 
 scalar_t__ nv_ro16 (struct nouveau_bios*,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*,int,scalar_t__,int,int,int) ; 

__attribute__((used)) static bool
init_io_condition_met(struct nvbios_init *init, u8 cond)
{
	struct nouveau_bios *bios = init->bios;
	u16 table = init_io_condition_table(init);
	if (table) {
		u16 port = nv_ro16(bios, table + (cond * 5) + 0);
		u8 index = nv_ro08(bios, table + (cond * 5) + 2);
		u8  mask = nv_ro08(bios, table + (cond * 5) + 3);
		u8 value = nv_ro08(bios, table + (cond * 5) + 4);
		trace("\t[0x%02x] (0x%04x[0x%02x] & 0x%02x) == 0x%02x\n",
		      cond, port, index, mask, value);
		return (init_rdvgai(init, port, index) & mask) == value;
	}
	return false;
}
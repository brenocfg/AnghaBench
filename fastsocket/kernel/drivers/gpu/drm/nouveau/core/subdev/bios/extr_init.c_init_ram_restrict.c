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
struct nvbios_init {int /*<<< orphan*/  bios; } ;

/* Variables and functions */
 int init_ram_restrict_strap (struct nvbios_init*) ; 
 int init_ram_restrict_table (struct nvbios_init*) ; 
 int nv_ro08 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u8
init_ram_restrict(struct nvbios_init *init)
{
	u8  strap = init_ram_restrict_strap(init);
	u16 table = init_ram_restrict_table(init);
	if (table)
		return nv_ro08(init->bios, table + strap);
	return 0x00;
}
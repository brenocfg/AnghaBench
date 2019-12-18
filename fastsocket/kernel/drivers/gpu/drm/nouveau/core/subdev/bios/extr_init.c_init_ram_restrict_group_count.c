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
struct nvbios_init {struct nouveau_bios* bios; } ;
struct nouveau_bios {int dummy; } ;
struct bit_entry {int version; int length; scalar_t__ offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  bit_entry (struct nouveau_bios*,char,struct bit_entry*) ; 
 int nv_ro08 (struct nouveau_bios*,scalar_t__) ; 

__attribute__((used)) static u8
init_ram_restrict_group_count(struct nvbios_init *init)
{
	struct nouveau_bios *bios = init->bios;
	struct bit_entry bit_M;

	if (!bit_entry(bios, 'M', &bit_M)) {
		if (bit_M.version == 1 && bit_M.length >= 5)
			return nv_ro08(bios, bit_M.offset + 2);
		if (bit_M.version == 2 && bit_M.length >= 3)
			return nv_ro08(bios, bit_M.offset + 0);
	}

	return 0x00;
}
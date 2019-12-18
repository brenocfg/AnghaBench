#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct nvbios_init {int ramcfg; TYPE_2__* bios; } ;
struct TYPE_3__ {int major; } ;
struct TYPE_4__ {TYPE_1__ version; } ;

/* Variables and functions */
 int init_rd32 (struct nvbios_init*,int) ; 

__attribute__((used)) static u8
init_ram_restrict_strap(struct nvbios_init *init)
{
	/* This appears to be the behaviour of the VBIOS parser, and *is*
	 * important to cache the NV_PEXTDEV_BOOT0 on later chipsets to
	 * avoid fucking up the memory controller (somehow) by reading it
	 * on every INIT_RAM_RESTRICT_ZM_GROUP opcode.
	 *
	 * Preserving the non-caching behaviour on earlier chipsets just
	 * in case *not* re-reading the strap causes similar breakage.
	 */
	if (!init->ramcfg || init->bios->version.major < 0x70)
		init->ramcfg = init_rd32(init, 0x101000);
	return (init->ramcfg & 0x00000003c) >> 2;
}
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
typedef  int u64 ;
typedef  int u32 ;
struct nouveau_gpuobj {int addr; int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  lower_32_bits (int) ; 
 int /*<<< orphan*/  nv_wo32 (struct nouveau_gpuobj*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int) ; 

__attribute__((used)) static void
nv50_vm_map_pgt(struct nouveau_gpuobj *pgd, u32 pde,
		struct nouveau_gpuobj *pgt[2])
{
	u64 phys = 0xdeadcafe00000000ULL;
	u32 coverage = 0;

	if (pgt[0]) {
		phys = 0x00000003 | pgt[0]->addr; /* present, 4KiB pages */
		coverage = (pgt[0]->size >> 3) << 12;
	} else
	if (pgt[1]) {
		phys = 0x00000001 | pgt[1]->addr; /* present */
		coverage = (pgt[1]->size >> 3) << 16;
	}

	if (phys & 1) {
		if (coverage <= 32 * 1024 * 1024)
			phys |= 0x60;
		else if (coverage <= 64 * 1024 * 1024)
			phys |= 0x40;
		else if (coverage <= 128 * 1024 * 1024)
			phys |= 0x20;
	}

	nv_wo32(pgd, (pde * 8) + 0, lower_32_bits(phys));
	nv_wo32(pgd, (pde * 8) + 4, upper_32_bits(phys));
}
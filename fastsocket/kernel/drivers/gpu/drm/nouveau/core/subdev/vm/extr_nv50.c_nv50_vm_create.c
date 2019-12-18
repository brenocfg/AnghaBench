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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct nouveau_vmmgr {int pgt_bits; } ;
struct nouveau_vm {int dummy; } ;

/* Variables and functions */
 int nouveau_vm_create (struct nouveau_vmmgr*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,struct nouveau_vm**) ; 

__attribute__((used)) static int
nv50_vm_create(struct nouveau_vmmgr *vmm, u64 offset, u64 length,
	       u64 mm_offset, struct nouveau_vm **pvm)
{
	u32 block = (1 << (vmm->pgt_bits + 12));
	if (block > length)
		block = length;

	return nouveau_vm_create(vmm, offset, length, mm_offset, block, pvm);
}
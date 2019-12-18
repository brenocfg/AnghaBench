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
typedef  scalar_t__ u32 ;
struct nouveau_vma {int access; } ;

/* Variables and functions */
 int NV_MEM_ACCESS_SYS ; 

__attribute__((used)) static inline u64
nvc0_vm_addr(struct nouveau_vma *vma, u64 phys, u32 memtype, u32 target)
{
	phys >>= 8;

	phys |= 0x00000001; /* present */
	if (vma->access & NV_MEM_ACCESS_SYS)
		phys |= 0x00000002;

	phys |= ((u64)target  << 32);
	phys |= ((u64)memtype << 36);

	return phys;
}
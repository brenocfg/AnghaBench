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
struct nouveau_vma {int access; } ;

/* Variables and functions */
 int NV_MEM_ACCESS_SYS ; 
 int NV_MEM_ACCESS_WO ; 

__attribute__((used)) static inline u64
vm_addr(struct nouveau_vma *vma, u64 phys, u32 memtype, u32 target)
{
	phys |= 1; /* present */
	phys |= (u64)memtype << 40;
	phys |= target << 4;
	if (vma->access & NV_MEM_ACCESS_SYS)
		phys |= (1 << 6);
	if (!(vma->access & NV_MEM_ACCESS_WO))
		phys |= (1 << 3);
	return phys;
}
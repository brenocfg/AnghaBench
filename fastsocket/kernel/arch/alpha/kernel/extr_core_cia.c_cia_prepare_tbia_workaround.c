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
typedef  int* vip ;

/* Variables and functions */
 int CIA_BROKEN_TBIA_BASE ; 
 int CIA_BROKEN_TBIA_SIZE ; 
 scalar_t__ CIA_IOC_PCI_Tn_BASE (int) ; 
 scalar_t__ CIA_IOC_PCI_Wn_BASE (int) ; 
 scalar_t__ CIA_IOC_PCI_Wn_MASK (int) ; 
 int PAGE_SHIFT ; 
 unsigned long* __alloc_bootmem (int,int,int /*<<< orphan*/ ) ; 
 int virt_to_phys (unsigned long*) ; 

__attribute__((used)) static inline void
cia_prepare_tbia_workaround(int window)
{
	unsigned long *ppte, pte;
	long i;

	/* Use minimal 1K map. */
	ppte = __alloc_bootmem(CIA_BROKEN_TBIA_SIZE, 32768, 0);
	pte = (virt_to_phys(ppte) >> (PAGE_SHIFT - 1)) | 1;

	for (i = 0; i < CIA_BROKEN_TBIA_SIZE / sizeof(unsigned long); ++i)
		ppte[i] = pte;

	*(vip)CIA_IOC_PCI_Wn_BASE(window) = CIA_BROKEN_TBIA_BASE | 3;
	*(vip)CIA_IOC_PCI_Wn_MASK(window)
	  = (CIA_BROKEN_TBIA_SIZE*1024 - 1) & 0xfff00000;
	*(vip)CIA_IOC_PCI_Tn_BASE(window) = virt_to_phys(ppte) >> 2;
}
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
typedef  int uint32_t ;
typedef  int ppnum_t ;
typedef  int pmap_paddr_t ;

/* Variables and functions */
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  cpu_number () ; 
 int /*<<< orphan*/  mp_disable_preemption () ; 
 int /*<<< orphan*/  mp_enable_preemption () ; 
 unsigned int pmap_cache_attributes (int) ; 
 int pmap_cpu_windows_copy_addr (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int pmap_map_cpu_windows_copy (int,int,unsigned int) ; 
 int /*<<< orphan*/  pmap_unmap_cpu_windows_copy (unsigned int) ; 

__attribute__((used)) static void
ml_phys_write_long_long(pmap_paddr_t paddr, unsigned long long data)
{
	unsigned int    index;
	unsigned int    wimg_bits;
	ppnum_t         pn = (paddr >> PAGE_SHIFT);

	mp_disable_preemption();
	wimg_bits = pmap_cache_attributes(pn);
	index = pmap_map_cpu_windows_copy(pn, VM_PROT_READ|VM_PROT_WRITE, wimg_bits);

	*(volatile unsigned long long *)(pmap_cpu_windows_copy_addr(cpu_number(), index)
	                        | ((uint32_t)paddr & PAGE_MASK)) = data;

	pmap_unmap_cpu_windows_copy(index);
	mp_enable_preemption();
}
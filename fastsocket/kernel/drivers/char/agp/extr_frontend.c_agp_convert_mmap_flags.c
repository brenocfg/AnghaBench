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
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 unsigned long VM_SHARED ; 
 unsigned long calc_vm_prot_bits (int) ; 
 int /*<<< orphan*/  vm_get_page_prot (unsigned long) ; 

__attribute__((used)) static pgprot_t agp_convert_mmap_flags(int prot)
{
	unsigned long prot_bits;

	prot_bits = calc_vm_prot_bits(prot) | VM_SHARED;
	return vm_get_page_prot(prot_bits);
}
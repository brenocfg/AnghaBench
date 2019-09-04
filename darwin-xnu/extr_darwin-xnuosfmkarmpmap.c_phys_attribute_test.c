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
typedef  scalar_t__ ppnum_t ;
typedef  int /*<<< orphan*/  pmap_paddr_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pa_test_bits (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ptoa (scalar_t__) ; 
 scalar_t__ vm_page_fictitious_addr ; 

__attribute__((used)) static boolean_t
phys_attribute_test(
	ppnum_t pn,
	unsigned int bits)
{
	pmap_paddr_t    pa = ptoa(pn);
	assert(pn != vm_page_fictitious_addr);
	return pa_test_bits(pa, bits);
}
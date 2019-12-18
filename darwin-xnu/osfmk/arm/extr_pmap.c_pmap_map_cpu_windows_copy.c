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
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int /*<<< orphan*/  ppnum_t ;

/* Variables and functions */
 unsigned int pmap_map_cpu_windows_copy_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

unsigned int
pmap_map_cpu_windows_copy(
	ppnum_t	pn,
	vm_prot_t prot,
	unsigned int wimg_bits)
{
	return pmap_map_cpu_windows_copy_internal(pn, prot, wimg_bits);
}
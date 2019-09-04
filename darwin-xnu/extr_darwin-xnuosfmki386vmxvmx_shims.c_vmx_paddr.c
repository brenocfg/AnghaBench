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
typedef  int /*<<< orphan*/  addr64_t ;

/* Variables and functions */
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  pmap_find_phys (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptoa_64 (int /*<<< orphan*/ ) ; 

addr64_t
vmx_paddr(void *va)
{
	return (ptoa_64(pmap_find_phys(kernel_pmap, (addr64_t)(uintptr_t)va)));
}
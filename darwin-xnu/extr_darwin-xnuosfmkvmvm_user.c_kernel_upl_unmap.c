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
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  int /*<<< orphan*/  upl_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  vm_upl_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
kernel_upl_unmap(
	vm_map_t	map,
	upl_t		upl)
{
	return vm_upl_unmap(map, upl);
}
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
typedef  int /*<<< orphan*/  vm_map_size_t ;
typedef  int /*<<< orphan*/  vm_map_copy_t ;
typedef  int /*<<< orphan*/  vm_map_address_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  vm_map_copyin_common (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

kern_return_t
vm_map_copyin(
	vm_map_t			src_map,
	vm_map_address_t	src_addr,
	vm_map_size_t		len,
	boolean_t			src_destroy,
	vm_map_copy_t		*copy_result)	/* OUT */
{
	return(vm_map_copyin_common(src_map, src_addr, len, src_destroy,
					FALSE, copy_result, FALSE));
}
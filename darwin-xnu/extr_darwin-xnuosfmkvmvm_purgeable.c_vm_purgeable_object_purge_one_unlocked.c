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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  vm_page_lock_queues () ; 
 int /*<<< orphan*/  vm_page_unlock_queues () ; 
 int /*<<< orphan*/  vm_purgeable_object_purge_one (int,int /*<<< orphan*/ ) ; 

boolean_t
vm_purgeable_object_purge_one_unlocked(
	int	force_purge_below_group)
{
	boolean_t	retval;

	vm_page_lock_queues();
	retval = vm_purgeable_object_purge_one(force_purge_below_group, 0);
	vm_page_unlock_queues();

	return retval;
}
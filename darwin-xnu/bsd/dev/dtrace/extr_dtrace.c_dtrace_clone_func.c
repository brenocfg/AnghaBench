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
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int DEVFS_CLONE_ALLOC ; 
 int DEVFS_CLONE_FREE ; 
 int dtrace_state_reserve () ; 

__attribute__((used)) static int
dtrace_clone_func(dev_t dev, int action)
{
#pragma unused(dev)

	if (action == DEVFS_CLONE_ALLOC) {
		return dtrace_state_reserve();
	}
	else if (action == DEVFS_CLONE_FREE) {
		return 0;
	}
	else return -1;
}
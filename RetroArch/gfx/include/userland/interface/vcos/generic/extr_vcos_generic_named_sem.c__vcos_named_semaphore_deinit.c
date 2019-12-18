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

/* Variables and functions */
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/ * sems_in_use ; 
 int /*<<< orphan*/  sems_pool ; 
 int /*<<< orphan*/  vcos_blockpool_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_delete (int /*<<< orphan*/ *) ; 

void _vcos_named_semaphore_deinit(void)
{
   vcos_blockpool_delete(&sems_pool);
   vcos_mutex_delete(&lock);
   sems_in_use = NULL;
}
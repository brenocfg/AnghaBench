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
 int /*<<< orphan*/  clean_writequeues () ; 
 int /*<<< orphan*/  con_cache ; 
 int /*<<< orphan*/  connections_lock ; 
 int /*<<< orphan*/  foreach_conn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_conn ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_conn ; 
 int /*<<< orphan*/  work_stop () ; 

void dlm_lowcomms_stop(void)
{
	/* Set all the flags to prevent any
	   socket activity.
	*/
	mutex_lock(&connections_lock);
	foreach_conn(stop_conn);
	mutex_unlock(&connections_lock);

	work_stop();

	mutex_lock(&connections_lock);
	clean_writequeues();

	foreach_conn(free_conn);

	mutex_unlock(&connections_lock);
	kmem_cache_destroy(con_cache);
}
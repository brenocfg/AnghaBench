#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* stop ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ oprofile_ops ; 
 scalar_t__ oprofile_started ; 
 int /*<<< orphan*/  start_mutex ; 
 int /*<<< orphan*/  stop_switch_worker () ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  wake_up_buffer_waiter () ; 

void oprofile_stop(void)
{
	mutex_lock(&start_mutex);
	if (!oprofile_started)
		goto out;
	oprofile_ops.stop();
	oprofile_started = 0;

	stop_switch_worker();

	/* wake up the daemon to read what remains */
	wake_up_buffer_waiter();
out:
	mutex_unlock(&start_mutex);
}
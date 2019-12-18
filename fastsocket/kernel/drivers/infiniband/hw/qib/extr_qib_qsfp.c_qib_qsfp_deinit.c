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
struct qib_qsfp_data {int dummy; } ;

/* Variables and functions */

void qib_qsfp_deinit(struct qib_qsfp_data *qd)
{
	/*
	 * There is nothing to do here for now.  our work is scheduled
	 * with queue_work(), and flush_workqueue() from remove_one
	 * will block until all work setup with queue_work()
	 * completes.
	 */
}
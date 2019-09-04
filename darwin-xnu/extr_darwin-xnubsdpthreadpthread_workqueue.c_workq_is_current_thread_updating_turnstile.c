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
struct workqueue {scalar_t__ wq_turnstile_updater; } ;

/* Variables and functions */
 scalar_t__ current_thread () ; 

bool
workq_is_current_thread_updating_turnstile(struct workqueue *wq)
{
	return wq->wq_turnstile_updater == current_thread();
}
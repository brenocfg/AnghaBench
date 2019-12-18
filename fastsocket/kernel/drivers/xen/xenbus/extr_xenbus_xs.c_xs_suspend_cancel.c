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
struct TYPE_2__ {int /*<<< orphan*/  transaction_mutex; int /*<<< orphan*/  watch_mutex; int /*<<< orphan*/  request_mutex; int /*<<< orphan*/  response_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 TYPE_1__ xs_state ; 

void xs_suspend_cancel(void)
{
	mutex_unlock(&xs_state.response_mutex);
	mutex_unlock(&xs_state.request_mutex);
	up_write(&xs_state.watch_mutex);
	up_write(&xs_state.transaction_mutex);
}
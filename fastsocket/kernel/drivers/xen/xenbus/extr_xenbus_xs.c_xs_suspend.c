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
struct TYPE_2__ {int /*<<< orphan*/  response_mutex; int /*<<< orphan*/  request_mutex; int /*<<< orphan*/  watch_mutex; int /*<<< orphan*/  transaction_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 TYPE_1__ xs_state ; 

void xs_suspend(void)
{
	down_write(&xs_state.transaction_mutex);
	down_write(&xs_state.watch_mutex);
	mutex_lock(&xs_state.request_mutex);
	mutex_lock(&xs_state.response_mutex);
}
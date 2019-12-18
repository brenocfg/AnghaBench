#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  settings_changed; int /*<<< orphan*/  expires; } ;
typedef  TYPE_1__ VCOS_TIMER_T ;

/* Variables and functions */
 int /*<<< orphan*/  _timespec_set_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_assert (TYPE_1__*) ; 

void vcos_pthreads_timer_cancel(VCOS_TIMER_T *timer)
{
   vcos_assert(timer);

   pthread_mutex_lock(&timer->lock);

   _timespec_set_zero(&timer->expires);
   pthread_cond_signal(&timer->settings_changed);

   pthread_mutex_unlock(&timer->lock);
}
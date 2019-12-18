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
struct timespec {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  orig_context; int /*<<< orphan*/  (* orig_expiration_routine ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  expires; int /*<<< orphan*/  settings_changed; int /*<<< orphan*/  quit; } ;
typedef  TYPE_1__ VCOS_TIMER_T ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 scalar_t__ _timespec_is_larger (int /*<<< orphan*/ *,struct timespec*) ; 
 scalar_t__ _timespec_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _timespec_set_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  pthread_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void* _timer_thread(void *arg)
{
   VCOS_TIMER_T *timer = (VCOS_TIMER_T*)arg;

   pthread_mutex_lock(&timer->lock);
   while (!timer->quit)
   {
      struct timespec now;

      /* Wait until next expiry time, or until timer's settings are changed */
      if (_timespec_is_zero(&timer->expires))
         pthread_cond_wait(&timer->settings_changed, &timer->lock);
      else
         pthread_cond_timedwait(&timer->settings_changed, &timer->lock, &timer->expires);

      /* See if the timer has expired - reloop if it didn't */
      clock_gettime(CLOCK_REALTIME, &now);
      if (_timespec_is_zero(&timer->expires) || _timespec_is_larger(&timer->expires, &now))
         continue;

      /* The timer has expired. Clear the expiry time and call the
       * expiration routine
       */
      _timespec_set_zero(&timer->expires);
      timer->orig_expiration_routine(timer->orig_context);
   }
   pthread_mutex_unlock(&timer->lock);

   return NULL;
}
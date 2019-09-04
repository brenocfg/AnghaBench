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
typedef  int /*<<< orphan*/  zbar_timer_t ;
typedef  int /*<<< orphan*/  zbar_mutex_t ;
typedef  int /*<<< orphan*/  zbar_event_t ;

/* Variables and functions */
 int WAIT_TIMEOUT ; 
 int WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _zbar_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zbar_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zbar_timer_check (int /*<<< orphan*/ *) ; 

int _zbar_event_wait (zbar_event_t *event,
                      zbar_mutex_t *lock,
                      zbar_timer_t *timeout)
{
    if(lock)
        _zbar_mutex_unlock(lock);
    int rc = WaitForSingleObject(*event, _zbar_timer_check(timeout));
    if(lock)
        _zbar_mutex_lock(lock);

    if(!rc)
        return(1); /* got event */
    if(rc == WAIT_TIMEOUT)
        return(0); /* timed out */
    return(-1); /* error (FIXME save info) */
}
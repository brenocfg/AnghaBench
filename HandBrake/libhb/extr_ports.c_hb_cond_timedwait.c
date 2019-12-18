#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct timespec {int tv_nsec; int tv_sec; } ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  sem; } ;
typedef  TYPE_1__ hb_lock_t ;
struct TYPE_6__ {int thread; int /*<<< orphan*/  cond; } ;
typedef  TYPE_2__ hb_cond_t ;

/* Variables and functions */
 int /*<<< orphan*/  acquire_sem (int /*<<< orphan*/ ) ; 
 int find_thread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_clock_gettime (struct timespec*) ; 
 int /*<<< orphan*/  pthread_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*) ; 
 int /*<<< orphan*/  release_sem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  suspend_thread (int) ; 

void hb_cond_timedwait( hb_cond_t * c, hb_lock_t * lock, int msec )
{
#if defined( SYS_BEOS )
    c->thread = find_thread( NULL );
    release_sem( lock->sem );
    suspend_thread( c->thread );
    acquire_sem( lock->sem );
    c->thread = -1;
#elif USE_PTHREAD
    struct timespec ts;
    hb_clock_gettime(&ts);
    ts.tv_nsec += (msec % 1000) * 1000000;
    ts.tv_sec += msec / 1000 + (ts.tv_nsec / 1000000000);
    ts.tv_nsec %= 1000000000;
    pthread_cond_timedwait( &c->cond, &lock->mutex, &ts );
#endif
}
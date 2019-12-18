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
struct TYPE_5__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  sem; } ;
typedef  TYPE_1__ hb_lock_t ;
struct TYPE_6__ {int thread; int /*<<< orphan*/  cond; } ;
typedef  TYPE_2__ hb_cond_t ;

/* Variables and functions */
 int /*<<< orphan*/  acquire_sem (int /*<<< orphan*/ ) ; 
 int find_thread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_sem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  suspend_thread (int) ; 

void hb_cond_wait( hb_cond_t * c, hb_lock_t * lock )
{
#if defined( SYS_BEOS )
    c->thread = find_thread( NULL );
    release_sem( lock->sem );
    suspend_thread( c->thread );
    acquire_sem( lock->sem );
    c->thread = -1;
#elif USE_PTHREAD
    pthread_cond_wait( &c->cond, &lock->mutex );
//#elif defined( SYS_CYGWIN )
//    SignalObjectAndWait( lock->mutex, c->event, INFINITE, FALSE );
//    WaitForSingleObject( lock->mutex, INFINITE );
#endif
}
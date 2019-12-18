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
struct TYPE_5__ {scalar_t__ state; } ;
typedef  TYPE_1__ thread_info ;
struct TYPE_6__ {int thread; int /*<<< orphan*/  cond; } ;
typedef  TYPE_2__ hb_cond_t ;

/* Variables and functions */
 scalar_t__ B_THREAD_SUSPENDED ; 
 int /*<<< orphan*/  get_thread_info (int,TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resume_thread (int) ; 
 int /*<<< orphan*/  snooze (int) ; 

void hb_cond_signal( hb_cond_t * c )
{
#if defined( SYS_BEOS )
    while( c->thread != -1 )
    {
        thread_info info;
        get_thread_info( c->thread, &info );
        if( info.state == B_THREAD_SUSPENDED )
        {
            resume_thread( c->thread );
            break;
        }
        /* Looks like we have been called between hb_cond_wait's
           release_sem() and suspend_thread() lines. Wait until the
           thread is actually suspended before we resume it */
        snooze( 5000 );
    }
#elif USE_PTHREAD
    pthread_cond_signal( &c->cond );
//#elif defined( SYS_CYGWIN )
//    PulseEvent( c->event );
#endif
}
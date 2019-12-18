#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  sem; } ;
typedef  TYPE_1__ hb_lock_t ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_sem (int /*<<< orphan*/ ) ; 

void hb_unlock( hb_lock_t * l )
{
#if defined( SYS_BEOS )
    release_sem( l->sem );
#elif USE_PTHREAD
    pthread_mutex_unlock( &l->mutex );
//#elif defined( SYS_CYGWIN )
//    ReleaseMutex( l->mutex );
#endif
}
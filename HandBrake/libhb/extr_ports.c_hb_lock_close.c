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
struct TYPE_4__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  sem; } ;
typedef  TYPE_1__ hb_lock_t ;

/* Variables and functions */
 int /*<<< orphan*/  delete_sem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

void hb_lock_close( hb_lock_t ** _l )
{
    hb_lock_t * l = *_l;

    if (l == NULL)
    {
        return;
    }
#if defined( SYS_BEOS )
    delete_sem( l->sem );
#elif USE_PTHREAD
    pthread_mutex_destroy( &l->mutex );
//#elif defined( SYS_CYGWIN )
//    CloseHandle( l->mutex );
#endif
    free( l );

    *_l = NULL;
}
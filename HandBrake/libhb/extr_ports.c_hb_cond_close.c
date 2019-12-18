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
struct TYPE_4__ {int /*<<< orphan*/  cond; } ;
typedef  TYPE_1__ hb_cond_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 

void hb_cond_close( hb_cond_t ** _c )
{
    hb_cond_t * c = *_c;

    if (c == NULL)
    {
        return;
    }
#if defined( SYS_BEOS )
#elif USE_PTHREAD
    pthread_cond_destroy( &c->cond );
//#elif defined( SYS_CYGWIN )
//    CloseHandle( c->event );
#endif
    free( c );

    *_c = NULL;
}
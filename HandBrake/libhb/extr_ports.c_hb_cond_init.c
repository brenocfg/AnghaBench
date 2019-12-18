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
struct TYPE_4__ {int thread; int /*<<< orphan*/  cond; } ;
typedef  TYPE_1__ hb_cond_t ;

/* Variables and functions */
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

hb_cond_t * hb_cond_init()
{
    hb_cond_t * c = calloc( sizeof( hb_cond_t ), 1 );

    if( c == NULL )
        return NULL;

#if defined( SYS_BEOS )
    c->thread = -1;
#elif USE_PTHREAD
    pthread_cond_init( &c->cond, NULL );
//#elif defined( SYS_CYGWIN )
//    c->event = CreateEvent( NULL, FALSE, FALSE, NULL );
#endif

    return c;
}
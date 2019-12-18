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
typedef  int /*<<< orphan*/  pthread_mutexattr_t ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  sem; } ;
typedef  TYPE_1__ hb_lock_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTHREAD_MUTEX_NORMAL ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  create_sem (int,char*) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutexattr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutexattr_settype (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

hb_lock_t * hb_lock_init()
{
    hb_lock_t * l = calloc( sizeof( hb_lock_t ), 1 );

#if defined( SYS_BEOS )
    l->sem = create_sem( 1, "sem" );
#elif USE_PTHREAD
    pthread_mutexattr_t mta;

    pthread_mutexattr_init(&mta);

#if defined( SYS_CYGWIN ) || defined( SYS_FREEBSD ) || defined ( __FreeBSD__ )
    pthread_mutexattr_settype(&mta, PTHREAD_MUTEX_NORMAL);
#endif

    pthread_mutex_init( &l->mutex, &mta );
//#elif defined( SYS_CYGWIN )
//    l->mutex = CreateMutex( 0, FALSE, 0 );
#endif

    return l;
}
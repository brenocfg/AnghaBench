#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ slock_t ;
struct TYPE_8__ {int /*<<< orphan*/  cond; } ;
typedef  TYPE_2__ scond_t ;

/* Variables and functions */
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  _scond_wait_win32 (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void scond_wait(scond_t *cond, slock_t *lock)
{
#ifdef USE_WIN32_THREADS
   _scond_wait_win32(cond, lock, INFINITE);
#else
   pthread_cond_wait(&cond->cond, &lock->lock);
#endif
}
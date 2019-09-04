#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int tid; } ;
struct TYPE_4__ {int lock; int /*<<< orphan*/  waiters; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 TYPE_2__* __pthread_self () ; 
 int /*<<< orphan*/  __wait (int*,int /*<<< orphan*/ *,int,int) ; 
 int a_cas (int*,int /*<<< orphan*/ ,int) ; 

int __lockfile(FILE *f)
{
#ifndef __EMSCRIPTEN__ // XXX EMSCRIPTEN: for now no pthreads; ignore locking
	int owner, tid = __pthread_self()->tid;
	if (f->lock == tid)
		return 0;
	while ((owner = a_cas(&f->lock, 0, tid)))
		__wait(&f->lock, &f->waiters, owner, 1);
#endif
	return 1;
}
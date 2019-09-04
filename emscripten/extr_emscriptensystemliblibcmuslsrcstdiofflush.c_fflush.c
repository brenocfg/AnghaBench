#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ wpos; scalar_t__ wbase; struct TYPE_8__* next; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  FUNLOCK (TYPE_1__*) ; 
 int __fflush_unlocked (TYPE_1__*) ; 
 TYPE_1__** __ofl_lock () ; 
 int /*<<< orphan*/  __ofl_unlock () ; 
 TYPE_1__* __stdout_used ; 

int fflush(FILE *f)
{
	int r;

	if (f) {
		FLOCK(f);
		r = __fflush_unlocked(f);
		FUNLOCK(f);
		return r;
	}

	r = __stdout_used ? fflush(__stdout_used) : 0;

	for (f=*__ofl_lock(); f; f=f->next) {
		FLOCK(f);
		if (f->wpos > f->wbase) r |= __fflush_unlocked(f);
		FUNLOCK(f);
	}
	__ofl_unlock();
	
	return r;
}
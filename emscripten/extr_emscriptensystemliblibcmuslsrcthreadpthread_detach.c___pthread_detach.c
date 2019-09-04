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
typedef  TYPE_1__* pthread_t ;
struct TYPE_4__ {int detached; int /*<<< orphan*/  exitlock; } ;

/* Variables and functions */
 int __pthread_join (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ a_swap (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __pthread_detach(pthread_t t)
{
	/* Cannot detach a thread that's already exiting */
	if (a_swap(t->exitlock, 1))
		return __pthread_join(t, 0);
	t->detached = 2;
	__unlock(t->exitlock);
	return 0;
}
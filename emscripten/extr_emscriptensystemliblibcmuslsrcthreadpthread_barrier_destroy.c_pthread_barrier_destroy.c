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
struct TYPE_3__ {scalar_t__ _b_limit; int _b_lock; } ;
typedef  TYPE_1__ pthread_barrier_t ;

/* Variables and functions */
 int INT_MAX ; 
 int /*<<< orphan*/  INT_MIN ; 
 int /*<<< orphan*/  __vm_wait () ; 
 int /*<<< orphan*/  __wait (int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a_or (int*,int /*<<< orphan*/ ) ; 

int pthread_barrier_destroy(pthread_barrier_t *b)
{
	if (b->_b_limit < 0) {
		if (b->_b_lock) {
			int v;
			a_or(&b->_b_lock, INT_MIN);
			while ((v = b->_b_lock) & INT_MAX)
				__wait(&b->_b_lock, 0, v, 0);
		}
		__vm_wait();
	}
	return 0;
}
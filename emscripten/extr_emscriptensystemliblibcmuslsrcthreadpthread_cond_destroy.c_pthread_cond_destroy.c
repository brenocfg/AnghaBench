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
struct TYPE_3__ {int _c_waiters; int /*<<< orphan*/  _c_seq; scalar_t__ _c_shared; } ;
typedef  TYPE_1__ pthread_cond_t ;

/* Variables and functions */
 int /*<<< orphan*/  __wait (int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __wake (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  a_or (int*,int) ; 

int pthread_cond_destroy(pthread_cond_t *c)
{
	if (c->_c_shared && c->_c_waiters) {
		int cnt;
		a_or(&c->_c_waiters, 0x80000000);
		a_inc(&c->_c_seq);
		__wake(&c->_c_seq, -1, 0);
		while ((cnt = c->_c_waiters) & 0x7fffffff)
			__wait(&c->_c_waiters, 0, cnt, 0);
	}
	return 0;
}
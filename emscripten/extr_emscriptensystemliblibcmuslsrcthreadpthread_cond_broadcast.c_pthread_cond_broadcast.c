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
struct TYPE_4__ {int /*<<< orphan*/  _c_seq; int /*<<< orphan*/  _c_waiters; int /*<<< orphan*/  _c_shared; } ;
typedef  TYPE_1__ pthread_cond_t ;

/* Variables and functions */
 int __private_cond_signal (TYPE_1__*,int) ; 
 int /*<<< orphan*/  __wake (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a_inc (int /*<<< orphan*/ *) ; 

int pthread_cond_broadcast(pthread_cond_t *c)
{
	if (!c->_c_shared) return __private_cond_signal(c, -1);
	if (!c->_c_waiters) return 0;
	a_inc(&c->_c_seq);
	__wake(&c->_c_seq, -1, 0);
	return 0;
}
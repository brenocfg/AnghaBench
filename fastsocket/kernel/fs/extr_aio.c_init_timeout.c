#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct aio_timeout {int /*<<< orphan*/  p; scalar_t__ timed_out; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  setup_timer_on_stack (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  timeout_func ; 

__attribute__((used)) static inline void init_timeout(struct aio_timeout *to)
{
	setup_timer_on_stack(&to->timer, timeout_func, (unsigned long) to);
	to->timed_out = 0;
	to->p = current;
}
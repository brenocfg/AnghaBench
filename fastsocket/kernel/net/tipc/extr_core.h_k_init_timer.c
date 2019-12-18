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
struct timer_list {int dummy; } ;
typedef  int /*<<< orphan*/  Handler ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*,struct timer_list*) ; 
 int /*<<< orphan*/  setup_timer (struct timer_list*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static inline void k_init_timer(struct timer_list *timer, Handler routine,
				unsigned long argument)
{
	dbg("initializing timer %p\n", timer);
	setup_timer(timer, routine, argument);
}
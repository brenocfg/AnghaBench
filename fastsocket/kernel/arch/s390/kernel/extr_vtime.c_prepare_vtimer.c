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
struct vtimer_list {scalar_t__ expires; int /*<<< orphan*/  cpu; int /*<<< orphan*/  function; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ VTIMER_MAX_SLICE ; 
 int /*<<< orphan*/  get_cpu () ; 
 int vtimer_pending (struct vtimer_list*) ; 

__attribute__((used)) static inline void prepare_vtimer(struct vtimer_list *timer)
{
	BUG_ON(!timer->function);
	BUG_ON(!timer->expires || timer->expires > VTIMER_MAX_SLICE);
	BUG_ON(vtimer_pending(timer));
	timer->cpu = get_cpu();
}
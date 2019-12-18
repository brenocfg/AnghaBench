#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void (* function ) (unsigned long) ;unsigned long data; } ;
struct sci_timer {TYPE_1__ timer; scalar_t__ cancel; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 

__attribute__((used)) static inline
void sci_init_timer(struct sci_timer *tmr, void (*fn)(unsigned long))
{
	tmr->timer.function = fn;
	tmr->timer.data = (unsigned long) tmr;
	tmr->cancel = 0;
	init_timer(&tmr->timer);
}
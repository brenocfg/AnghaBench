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
struct hrtimer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug_hrtimer_activate (struct hrtimer*) ; 
 int /*<<< orphan*/  trace_hrtimer_start (struct hrtimer*) ; 

__attribute__((used)) static inline void debug_activate(struct hrtimer *timer)
{
	debug_hrtimer_activate(timer);
	trace_hrtimer_start(timer);
}
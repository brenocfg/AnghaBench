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
struct slow_work {int /*<<< orphan*/  mark; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME ; 

__attribute__((used)) static inline void slow_work_mark_time(struct slow_work *work)
{
#ifdef CONFIG_SLOW_WORK_DEBUG
	work->mark = CURRENT_TIME;
#endif
}
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
typedef  int /*<<< orphan*/  ktime_t ;
typedef  enum hrtimer_mode { ____Placeholder_hrtimer_mode } hrtimer_mode ;

/* Variables and functions */
 int /*<<< orphan*/  jprobe_return () ; 
 int /*<<< orphan*/  lkdtm_handler () ; 

__attribute__((used)) static int jp_hrtimer_start(struct hrtimer *timer, ktime_t tim,
			    const enum hrtimer_mode mode)
{
	lkdtm_handler();
	jprobe_return();
	return 0;
}
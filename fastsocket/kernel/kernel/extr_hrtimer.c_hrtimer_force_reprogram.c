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
struct hrtimer_cpu_base {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void
hrtimer_force_reprogram(struct hrtimer_cpu_base *base, int skip_equal) { }
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
struct TYPE_2__ {int /*<<< orphan*/  rev_g_coeff; } ;
struct wm8350 {TYPE_1__ power; } ;

/* Variables and functions */

__attribute__((used)) static inline int wm8350_charge_time_min(struct wm8350 *wm8350, int min)
{
	if (!wm8350->power.rev_g_coeff)
		return (((min - 30) / 15) & 0xf) << 8;
	else
		return (((min - 30) / 30) & 0xf) << 8;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  shift; int /*<<< orphan*/  scale; int /*<<< orphan*/  ns_base; int /*<<< orphan*/  tsc_base; } ;
typedef  TYPE_1__ pal_rtc_nanotime_t ;

/* Variables and functions */
 int /*<<< orphan*/  commpage_set_nanotime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
rtc_nanotime_set_commpage(pal_rtc_nanotime_t *rntp)
{
	commpage_set_nanotime(rntp->tsc_base, rntp->ns_base, rntp->scale, rntp->shift);
}
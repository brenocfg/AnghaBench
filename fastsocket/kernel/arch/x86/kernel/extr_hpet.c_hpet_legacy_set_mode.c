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
struct clock_event_device {int dummy; } ;
typedef  enum clock_event_mode { ____Placeholder_clock_event_mode } clock_event_mode ;

/* Variables and functions */
 int /*<<< orphan*/  hpet_set_mode (int,struct clock_event_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hpet_legacy_set_mode(enum clock_event_mode mode,
			struct clock_event_device *evt)
{
	hpet_set_mode(mode, evt, 0);
}
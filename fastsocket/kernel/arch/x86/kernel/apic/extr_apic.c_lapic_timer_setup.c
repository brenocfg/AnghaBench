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
struct clock_event_device {int features; } ;
typedef  enum clock_event_mode { ____Placeholder_clock_event_mode } clock_event_mode ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_LVTT ; 
 unsigned int APIC_LVT_MASKED ; 
 int /*<<< orphan*/  APIC_TMICT ; 
 int CLOCK_EVT_FEAT_DUMMY ; 
#define  CLOCK_EVT_MODE_ONESHOT 132 
#define  CLOCK_EVT_MODE_PERIODIC 131 
#define  CLOCK_EVT_MODE_RESUME 130 
#define  CLOCK_EVT_MODE_SHUTDOWN 129 
#define  CLOCK_EVT_MODE_UNUSED 128 
 unsigned int LOCAL_TIMER_VECTOR ; 
 int /*<<< orphan*/  __setup_APIC_LVTT (int /*<<< orphan*/ ,int,int) ; 
 unsigned int apic_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apic_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  calibration_result ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static void lapic_timer_setup(enum clock_event_mode mode,
			      struct clock_event_device *evt)
{
	unsigned long flags;
	unsigned int v;

	/* Lapic used as dummy for broadcast ? */
	if (evt->features & CLOCK_EVT_FEAT_DUMMY)
		return;

	local_irq_save(flags);

	switch (mode) {
	case CLOCK_EVT_MODE_PERIODIC:
	case CLOCK_EVT_MODE_ONESHOT:
		__setup_APIC_LVTT(calibration_result,
				  mode != CLOCK_EVT_MODE_PERIODIC, 1);
		break;
	case CLOCK_EVT_MODE_UNUSED:
	case CLOCK_EVT_MODE_SHUTDOWN:
		v = apic_read(APIC_LVTT);
		v |= (APIC_LVT_MASKED | LOCAL_TIMER_VECTOR);
		apic_write(APIC_LVTT, v);
		apic_write(APIC_TMICT, 0xffffffff);
		break;
	case CLOCK_EVT_MODE_RESUME:
		/* Nothing to do here */
		break;
	}

	local_irq_restore(flags);
}
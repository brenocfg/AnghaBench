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
typedef  int u8 ;
struct clock_event_device {int dummy; } ;
typedef  enum clock_event_mode { ____Placeholder_clock_event_mode } clock_event_mode ;

/* Variables and functions */
 int /*<<< orphan*/  A20R_PT_CLOCK_BASE ; 
#define  CLOCK_EVT_MODE_ONESHOT 132 
#define  CLOCK_EVT_MODE_PERIODIC 131 
#define  CLOCK_EVT_MODE_RESUME 130 
#define  CLOCK_EVT_MODE_SHUTDOWN 129 
#define  CLOCK_EVT_MODE_UNUSED 128 
 int SNI_COUNTER0_DIV ; 
 int SNI_COUNTER2_DIV ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void a20r_set_mode(enum clock_event_mode mode,
                          struct clock_event_device *evt)
{
	switch (mode) {
	case CLOCK_EVT_MODE_PERIODIC:
		*(volatile u8 *)(A20R_PT_CLOCK_BASE + 12) = 0x34;
		wmb();
		*(volatile u8 *)(A20R_PT_CLOCK_BASE +  0) = SNI_COUNTER0_DIV;
		wmb();
		*(volatile u8 *)(A20R_PT_CLOCK_BASE +  0) = SNI_COUNTER0_DIV >> 8;
		wmb();

		*(volatile u8 *)(A20R_PT_CLOCK_BASE + 12) = 0xb4;
		wmb();
		*(volatile u8 *)(A20R_PT_CLOCK_BASE +  8) = SNI_COUNTER2_DIV;
		wmb();
		*(volatile u8 *)(A20R_PT_CLOCK_BASE +  8) = SNI_COUNTER2_DIV >> 8;
		wmb();

                break;
        case CLOCK_EVT_MODE_ONESHOT:
        case CLOCK_EVT_MODE_UNUSED:
        case CLOCK_EVT_MODE_SHUTDOWN:
                break;
        case CLOCK_EVT_MODE_RESUME:
                break;
        }
}
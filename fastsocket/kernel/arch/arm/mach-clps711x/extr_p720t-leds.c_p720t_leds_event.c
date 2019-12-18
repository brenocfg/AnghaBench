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
typedef  int u32 ;
typedef  int led_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  PDDR ; 
 int clps_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clps_writeb (int,int /*<<< orphan*/ ) ; 
#define  led_idle_end 130 
#define  led_idle_start 129 
#define  led_timer 128 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static void p720t_leds_event(led_event_t ledevt)
{
	unsigned long flags;
	u32 pddr;

	local_irq_save(flags);
	switch(ledevt) {
	case led_idle_start:
		break;

	case led_idle_end:
		break;

	case led_timer:
		pddr = clps_readb(PDDR);
		clps_writeb(pddr ^ 1, PDDR);
		break;

	default:
		break;
	}

	local_irq_restore(flags);
}
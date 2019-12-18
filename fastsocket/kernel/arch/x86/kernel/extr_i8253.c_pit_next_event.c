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

/* Variables and functions */
 int /*<<< orphan*/  PIT_CH0 ; 
 int /*<<< orphan*/  i8253_lock ; 
 int /*<<< orphan*/  outb_pit (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pit_next_event(unsigned long delta, struct clock_event_device *evt)
{
	spin_lock(&i8253_lock);
	outb_pit(delta & 0xff , PIT_CH0);	/* LSB */
	outb_pit(delta >> 8 , PIT_CH0);		/* MSB */
	spin_unlock(&i8253_lock);

	return 0;
}
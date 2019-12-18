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
struct kbd_struct {int /*<<< orphan*/  ledmode; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_SHOW_FLAGS ; 
 int /*<<< orphan*/  LED_SHOW_IOCTL ; 
 unsigned int ledioctl ; 
 int /*<<< orphan*/  set_leds () ; 

void setledstate(struct kbd_struct *kbd, unsigned int led)
{
	if (!(led & ~7)) {
		ledioctl = led;
		kbd->ledmode = LED_SHOW_IOCTL;
	} else
		kbd->ledmode = LED_SHOW_FLAGS;
	set_leds();
}
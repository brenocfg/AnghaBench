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
struct TYPE_3__ {int speed; } ;
typedef  TYPE_1__ wavnc_port_info ;

/* Variables and functions */

__attribute__((used)) static unsigned int
waveartist_get_speed(wavnc_port_info *portc)
{
	unsigned int speed;

	/*
	 * program the speed, channels, bits
	 */
	if (portc->speed == 8000)
		speed = 0x2E71;
	else if (portc->speed == 11025)
		speed = 0x4000;
	else if (portc->speed == 22050)
		speed = 0x8000;
	else if (portc->speed == 44100)
		speed = 0x0;
	else {
		/*
		 * non-standard - just calculate
		 */
		speed = portc->speed << 16;

		speed = (speed / 44100) & 65535;
	}

	return speed;
}
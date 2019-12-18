#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int speed; } ;
typedef  TYPE_1__ wavnc_port_info ;
struct TYPE_4__ {scalar_t__ portc; } ;

/* Variables and functions */
 TYPE_2__** audio_devs ; 

__attribute__((used)) static int
waveartist_set_speed(int dev, int arg)
{
	wavnc_port_info *portc = (wavnc_port_info *) audio_devs[dev]->portc;

	if (arg <= 0)
		return portc->speed;

	if (arg < 5000)
		arg = 5000;
	if (arg > 44100)
		arg = 44100;

	portc->speed = arg;
	return portc->speed;

}
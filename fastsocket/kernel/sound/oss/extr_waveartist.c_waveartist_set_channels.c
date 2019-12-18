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
struct TYPE_3__ {short channels; } ;
typedef  TYPE_1__ wavnc_port_info ;
struct TYPE_4__ {scalar_t__ portc; } ;

/* Variables and functions */
 TYPE_2__** audio_devs ; 

__attribute__((used)) static short
waveartist_set_channels(int dev, short arg)
{
	wavnc_port_info *portc = (wavnc_port_info *) audio_devs[dev]->portc;

	if (arg != 1 && arg != 2)
		return portc->channels;

	portc->channels = arg;
	return arg;
}
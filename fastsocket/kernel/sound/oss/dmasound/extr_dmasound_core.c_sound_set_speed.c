#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int speed; } ;
struct TYPE_7__ {int speed; } ;
struct TYPE_5__ {int max_dsp_speed; } ;
struct TYPE_8__ {scalar_t__ minDev; TYPE_2__ soft; TYPE_3__ dsp; TYPE_1__ mach; } ;

/* Variables and functions */
 scalar_t__ SND_DEV_DSP ; 
 TYPE_4__ dmasound ; 

__attribute__((used)) static int sound_set_speed(int speed)
{
	if (speed < 0)
		return dmasound.soft.speed;

	/* trap out-of-range speed settings.
	   at present we allow (arbitrarily) low rates - using soft
	   up-conversion - but we can't allow > max because there is
	   no soft down-conversion.
	*/
	if (dmasound.mach.max_dsp_speed &&
	   (speed > dmasound.mach.max_dsp_speed))
		speed = dmasound.mach.max_dsp_speed ;

	dmasound.soft.speed = speed;

	if (dmasound.minDev == SND_DEV_DSP)
		dmasound.dsp.speed = dmasound.soft.speed;

	return dmasound.soft.speed;
}
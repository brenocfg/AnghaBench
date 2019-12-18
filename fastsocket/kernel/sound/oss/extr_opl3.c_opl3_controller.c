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
struct TYPE_4__ {int nr_voice; TYPE_1__* voc; } ;
struct TYPE_3__ {int bender_range; int volume; int panning; } ;

/* Variables and functions */
#define  CTL_MAIN_VOLUME 131 
#define  CTL_PAN 130 
#define  CTRL_PITCH_BENDER 129 
#define  CTRL_PITCH_BENDER_RANGE 128 
 int /*<<< orphan*/  bend_pitch (int,int,int) ; 
 TYPE_2__* devc ; 

__attribute__((used)) static void opl3_controller (int dev, int voice, int ctrl_num, int value)
{
	if (voice < 0 || voice >= devc->nr_voice)
		return;

	switch (ctrl_num)
	{
		case CTRL_PITCH_BENDER:
			bend_pitch(dev, voice, value);
			break;

		case CTRL_PITCH_BENDER_RANGE:
			devc->voc[voice].bender_range = value;
			break;

		case CTL_MAIN_VOLUME:
			devc->voc[voice].volume = value / 128;
			break;

		case CTL_PAN:
			devc->voc[voice].panning = (value * 2) - 128;
			break;
	}
}
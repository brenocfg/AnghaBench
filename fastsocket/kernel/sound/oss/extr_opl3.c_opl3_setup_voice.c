#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct channel_info {int* controllers; int /*<<< orphan*/  bender_range; int /*<<< orphan*/  pgm_num; } ;
struct TYPE_6__ {TYPE_1__* voc; } ;
struct TYPE_5__ {struct channel_info* chn_info; } ;
struct TYPE_4__ {int volume; int panning; int /*<<< orphan*/  bender_range; scalar_t__ bender; } ;

/* Variables and functions */
 size_t CTL_MAIN_VOLUME ; 
 size_t CTL_PAN ; 
 TYPE_3__* devc ; 
 int /*<<< orphan*/  opl3_set_instr (int,int,int /*<<< orphan*/ ) ; 
 TYPE_2__** synth_devs ; 

__attribute__((used)) static void opl3_setup_voice(int dev, int voice, int chn)
{
	struct channel_info *info =
	&synth_devs[dev]->chn_info[chn];

	opl3_set_instr(dev, voice, info->pgm_num);

	devc->voc[voice].bender = 0;
	devc->voc[voice].bender_range = info->bender_range;
	devc->voc[voice].volume = info->controllers[CTL_MAIN_VOLUME];
	devc->voc[voice].panning = (info->controllers[CTL_PAN] * 2) - 128;
}
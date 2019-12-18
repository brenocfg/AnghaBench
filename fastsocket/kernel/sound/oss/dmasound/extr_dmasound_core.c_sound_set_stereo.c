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
struct TYPE_5__ {int stereo; } ;
struct TYPE_4__ {int stereo; } ;
struct TYPE_6__ {scalar_t__ minDev; TYPE_2__ dsp; TYPE_1__ soft; } ;

/* Variables and functions */
 scalar_t__ SND_DEV_DSP ; 
 TYPE_3__ dmasound ; 

__attribute__((used)) static int sound_set_stereo(int stereo)
{
	if (stereo < 0)
		return dmasound.soft.stereo;

	stereo = !!stereo;    /* should be 0 or 1 now */

	dmasound.soft.stereo = stereo;
	if (dmasound.minDev == SND_DEV_DSP)
		dmasound.dsp.stereo = stereo;

	return stereo;
}
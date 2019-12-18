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
struct TYPE_6__ {int /*<<< orphan*/  gamma; int /*<<< orphan*/  brightness; int /*<<< orphan*/  contrast; int /*<<< orphan*/  saturation; int /*<<< orphan*/  hue; } ;
struct TYPE_5__ {int /*<<< orphan*/  burst_phase; int /*<<< orphan*/  bleed; int /*<<< orphan*/  fringing; int /*<<< orphan*/  artifacts; int /*<<< orphan*/  resolution; int /*<<< orphan*/  sharpness; } ;
struct TYPE_4__ {int /*<<< orphan*/  gamma; int /*<<< orphan*/  brightness; int /*<<< orphan*/  contrast; int /*<<< orphan*/  saturation; int /*<<< orphan*/  hue; int /*<<< orphan*/  burst_phase; int /*<<< orphan*/  bleed; int /*<<< orphan*/  fringing; int /*<<< orphan*/  artifacts; int /*<<< orphan*/  resolution; int /*<<< orphan*/  sharpness; } ;

/* Variables and functions */
 TYPE_3__ COLOURS_NTSC_setup ; 
 int FILTER_NTSC_PRESET_CUSTOM ; 
 int FILTER_NTSC_PRESET_SIZE ; 
 TYPE_2__ FILTER_NTSC_setup ; 
 scalar_t__ Util_almostequal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double) ; 
 TYPE_1__** presets ; 

int FILTER_NTSC_GetPreset(void)
{
	int i;

	for (i = 0; i < FILTER_NTSC_PRESET_SIZE; i ++) {
		if (Util_almostequal(FILTER_NTSC_setup.sharpness, presets[i]->sharpness, 0.001) &&
		    Util_almostequal(FILTER_NTSC_setup.resolution, presets[i]->resolution, 0.001) &&
		    Util_almostequal(FILTER_NTSC_setup.artifacts, presets[i]->artifacts, 0.001) &&
		    Util_almostequal(FILTER_NTSC_setup.fringing, presets[i]->fringing, 0.001) &&
		    Util_almostequal(FILTER_NTSC_setup.bleed, presets[i]->bleed, 0.001) &&
		    Util_almostequal(FILTER_NTSC_setup.burst_phase, presets[i]->burst_phase, 0.001) &&
		    Util_almostequal(COLOURS_NTSC_setup.hue, presets[i]->hue, 0.001) &&
		    Util_almostequal(COLOURS_NTSC_setup.saturation, presets[i]->saturation, 0.001) &&
		    Util_almostequal(COLOURS_NTSC_setup.contrast, presets[i]->contrast, 0.001) &&
		    Util_almostequal(COLOURS_NTSC_setup.brightness, presets[i]->brightness, 0.001) &&
		    Util_almostequal(COLOURS_NTSC_setup.gamma, presets[i]->gamma, 0.001))
			return i; 
	}
	return FILTER_NTSC_PRESET_CUSTOM;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  gamma; int /*<<< orphan*/  brightness; int /*<<< orphan*/  contrast; int /*<<< orphan*/  saturation; int /*<<< orphan*/  hue; } ;
struct TYPE_4__ {int /*<<< orphan*/  gamma; int /*<<< orphan*/  brightness; int /*<<< orphan*/  contrast; int /*<<< orphan*/  saturation; int /*<<< orphan*/  hue; } ;

/* Variables and functions */
 TYPE_3__ COLOURS_NTSC_setup ; 
 int FILTER_NTSC_PRESET_CUSTOM ; 
 TYPE_1__ FILTER_NTSC_setup ; 
 TYPE_1__** presets ; 

void FILTER_NTSC_SetPreset(int preset)
{
	if (preset < FILTER_NTSC_PRESET_CUSTOM) {
		FILTER_NTSC_setup = *presets[preset];

		/* Copy settings from the preset to NTSC setup. */
		COLOURS_NTSC_setup.hue = FILTER_NTSC_setup.hue;
		COLOURS_NTSC_setup.saturation = FILTER_NTSC_setup.saturation;
		COLOURS_NTSC_setup.contrast = FILTER_NTSC_setup.contrast;
		COLOURS_NTSC_setup.brightness = FILTER_NTSC_setup.brightness;
		COLOURS_NTSC_setup.gamma = FILTER_NTSC_setup.gamma;
	}
}
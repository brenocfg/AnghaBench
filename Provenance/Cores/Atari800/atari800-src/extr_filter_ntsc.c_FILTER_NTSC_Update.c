#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  atari_ntsc_t ;
struct TYPE_7__ {int /*<<< orphan*/  adjust; scalar_t__ loaded; } ;
struct TYPE_6__ {double hue; double saturation; double contrast; double brightness; } ;
struct TYPE_5__ {int burst_phase; double hue; double saturation; double contrast; double brightness; double* yiq_palette; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLOURS_NTSC_GetYIQ (double*,int) ; 
 TYPE_4__ COLOURS_NTSC_external ; 
 TYPE_3__ COLOURS_NTSC_setup ; 
 TYPE_1__ FILTER_NTSC_setup ; 
 int M_PI ; 
 int /*<<< orphan*/  atari_ntsc_init (int /*<<< orphan*/ *,TYPE_1__*) ; 

void FILTER_NTSC_Update(atari_ntsc_t *filter)
{
	double yiq_table[768];

	COLOURS_NTSC_GetYIQ(yiq_table, FILTER_NTSC_setup.burst_phase * M_PI);
	/* The gamma setting is not used in atari_ntsc (palette generation is
	   placed in another module), so below we do not set the gamma field
	   of the FILTER_NTSC_setup structure. */
	if (COLOURS_NTSC_external.loaded && !COLOURS_NTSC_external.adjust) {
		/* External palette must not be adjusted, so FILTER_NTSC
		   settings are set to defaults so they don't change the source
		   palette in any way. */
		FILTER_NTSC_setup.hue = 0.0;
		FILTER_NTSC_setup.saturation = 0.0;
		FILTER_NTSC_setup.contrast = 0.0;
		FILTER_NTSC_setup.brightness = 0.0;
	} else {
		/* It's either generated palette, or external palette with
		   need for adjustments. Copy values from
		   COLOURS_NTSC_setup to FILTER_NTSC_setup. */
		FILTER_NTSC_setup.hue = COLOURS_NTSC_setup.hue;
		FILTER_NTSC_setup.saturation = COLOURS_NTSC_setup.saturation;
		FILTER_NTSC_setup.contrast = COLOURS_NTSC_setup.contrast;
		FILTER_NTSC_setup.brightness = COLOURS_NTSC_setup.brightness;
	}

	FILTER_NTSC_setup.yiq_palette = yiq_table;
	atari_ntsc_init(filter, &FILTER_NTSC_setup);
}
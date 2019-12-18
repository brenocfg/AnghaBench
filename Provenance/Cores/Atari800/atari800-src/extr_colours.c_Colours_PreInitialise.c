#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  COLOURS_NTSC_RestoreDefaults () ; 
 int /*<<< orphan*/  COLOURS_NTSC_setup ; 
 int /*<<< orphan*/  COLOURS_PAL_RestoreDefaults () ; 
 int /*<<< orphan*/  COLOURS_PAL_setup ; 
 size_t COLOURS_PRESET_STANDARD ; 
 int /*<<< orphan*/ * presets ; 

void Colours_PreInitialise(void)
{
	/* Copy the default setup for both NTSC and PAL. */
	COLOURS_NTSC_setup = COLOURS_PAL_setup = presets[COLOURS_PRESET_STANDARD];
	COLOURS_NTSC_RestoreDefaults();
	COLOURS_PAL_RestoreDefaults();
}
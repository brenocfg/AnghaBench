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
 int /*<<< orphan*/  COLOURS_PRESET_STANDARD ; 
 int /*<<< orphan*/  Colours_SetPreset (int /*<<< orphan*/ ) ; 

void Colours_RestoreDefaults(void)
{
	Colours_SetPreset(COLOURS_PRESET_STANDARD);
}
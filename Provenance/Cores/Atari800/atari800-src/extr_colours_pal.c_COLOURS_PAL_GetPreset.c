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
struct TYPE_4__ {int /*<<< orphan*/  color_delay; } ;
struct TYPE_3__ {int /*<<< orphan*/  color_delay; } ;
typedef  int /*<<< orphan*/  Colours_preset_t ;

/* Variables and functions */
 TYPE_2__ COLOURS_PAL_setup ; 
 int /*<<< orphan*/  COLOURS_PRESET_CUSTOM ; 
 int /*<<< orphan*/  COLOURS_PRESET_STANDARD ; 
 scalar_t__ Util_almostequal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double) ; 
 TYPE_1__ default_setup ; 

Colours_preset_t COLOURS_PAL_GetPreset()
{
	if (Util_almostequal(COLOURS_PAL_setup.color_delay, default_setup.color_delay, 0.001))
		return COLOURS_PRESET_STANDARD;
	return COLOURS_PRESET_CUSTOM;
}
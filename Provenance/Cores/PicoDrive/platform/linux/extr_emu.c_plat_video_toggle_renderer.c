#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int renderer; } ;

/* Variables and functions */
 int RT_COUNT ; 
 int /*<<< orphan*/  apply_renderer () ; 
 TYPE_1__ currentConfig ; 
 int /*<<< orphan*/  emu_status_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * renderer_names ; 

void plat_video_toggle_renderer(int change, int is_menu)
{
	currentConfig.renderer += change;
	if      (currentConfig.renderer >= RT_COUNT)
		currentConfig.renderer = 0;
	else if (currentConfig.renderer < 0)
		currentConfig.renderer = RT_COUNT - 1;

	if (!is_menu)
		apply_renderer();

	emu_status_msg(renderer_names[currentConfig.renderer]);
}
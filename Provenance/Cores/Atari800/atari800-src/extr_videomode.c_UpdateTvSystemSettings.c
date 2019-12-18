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
struct TYPE_2__ {int /*<<< orphan*/  asp_ratio; } ;

/* Variables and functions */
 scalar_t__ Atari800_TV_PAL ; 
 scalar_t__ Atari800_tv_mode ; 
 size_t VIDEOMODE_MODE_NORMAL ; 
 TYPE_1__* display_modes ; 
 int /*<<< orphan*/  pixel_aspect_ratio_ntsc ; 
 int /*<<< orphan*/  pixel_aspect_ratio_pal ; 

__attribute__((used)) static void UpdateTvSystemSettings(void)
{
	display_modes[VIDEOMODE_MODE_NORMAL].asp_ratio = Atari800_tv_mode == Atari800_TV_PAL ? pixel_aspect_ratio_pal : pixel_aspect_ratio_ntsc;
}
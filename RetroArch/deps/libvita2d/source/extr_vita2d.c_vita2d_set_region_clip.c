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
typedef  int /*<<< orphan*/  SceGxmRegionClipMode ;

/* Variables and functions */
 int /*<<< orphan*/  _vita2d_context ; 
 int /*<<< orphan*/  sceGxmSetRegionClip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,unsigned int) ; 

void vita2d_set_region_clip(SceGxmRegionClipMode mode, unsigned int x_min, unsigned int y_min, unsigned int x_max, unsigned int y_max)
{
	sceGxmSetRegionClip(_vita2d_context, mode, x_min, y_min, x_max, y_max);
}
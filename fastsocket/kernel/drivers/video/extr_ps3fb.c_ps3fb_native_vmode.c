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
struct fb_videomode {int dummy; } ;
typedef  enum ps3av_mode_num { ____Placeholder_ps3av_mode_num } ps3av_mode_num ;

/* Variables and functions */
 int FIRST_NATIVE_MODE_INDEX ; 
 struct fb_videomode const* ps3fb_modedb ; 

__attribute__((used)) static const struct fb_videomode *ps3fb_native_vmode(enum ps3av_mode_num id)
{
	return &ps3fb_modedb[FIRST_NATIVE_MODE_INDEX + id - 1];
}
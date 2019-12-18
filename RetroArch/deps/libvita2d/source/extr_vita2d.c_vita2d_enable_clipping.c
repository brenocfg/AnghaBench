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
 int /*<<< orphan*/  clip_rect_x_max ; 
 int /*<<< orphan*/  clip_rect_x_min ; 
 int /*<<< orphan*/  clip_rect_y_max ; 
 int /*<<< orphan*/  clip_rect_y_min ; 
 int clipping_enabled ; 
 int /*<<< orphan*/  vita2d_set_clip_rectangle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vita2d_enable_clipping()
{
	clipping_enabled = 1;
	vita2d_set_clip_rectangle(clip_rect_x_min, clip_rect_y_min, clip_rect_x_max, clip_rect_y_max);
}
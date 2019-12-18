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
typedef  int /*<<< orphan*/  vita2d_texture ;

/* Variables and functions */
 int /*<<< orphan*/  vita2d_draw_texture_rotate_hotspot (int /*<<< orphan*/  const*,float,float,float,float,float) ; 
 float vita2d_texture_get_height (int /*<<< orphan*/  const*) ; 
 float vita2d_texture_get_width (int /*<<< orphan*/  const*) ; 

void vita2d_draw_texture_rotate(const vita2d_texture *texture, float x, float y, float rad)
{
	vita2d_draw_texture_rotate_hotspot(texture, x, y, rad,
		vita2d_texture_get_width(texture)/2.0f,
		vita2d_texture_get_height(texture)/2.0f);
}
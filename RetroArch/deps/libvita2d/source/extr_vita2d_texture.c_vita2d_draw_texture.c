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
 int /*<<< orphan*/  draw_texture_generic (int /*<<< orphan*/  const*,float,float) ; 
 int /*<<< orphan*/  set_texture_program () ; 
 int /*<<< orphan*/  set_texture_wvp_uniform () ; 

void vita2d_draw_texture(const vita2d_texture *texture, float x, float y)
{
	set_texture_program();
	set_texture_wvp_uniform();
	draw_texture_generic(texture, x, y);
}
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
struct TYPE_2__ {int width; int height; } ;
struct bttv_crop {int min_scaled_width; int min_scaled_height; int max_scaled_width; int max_scaled_height; TYPE_1__ rect; } ;

/* Variables and functions */
 int max (int,int) ; 

__attribute__((used)) static void
bttv_crop_calc_limits(struct bttv_crop *c)
{
	/* Scale factor min. 1:1, max. 16:1. Min. image size
	   48 x 32. Scaled width must be a multiple of 4. */

	if (1) {
		/* For bug compatibility with VIDIOCGCAP and image
		   size checks in earlier driver versions. */
		c->min_scaled_width = 48;
		c->min_scaled_height = 32;
	} else {
		c->min_scaled_width =
			(max(48, c->rect.width >> 4) + 3) & ~3;
		c->min_scaled_height =
			max(32, c->rect.height >> 4);
	}

	c->max_scaled_width  = c->rect.width & ~3;
	c->max_scaled_height = c->rect.height;
}
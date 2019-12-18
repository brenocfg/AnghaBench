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
struct fb_cmap {int dummy; } ;

/* Variables and functions */
 struct fb_cmap const default_16_colors ; 
 struct fb_cmap const default_2_colors ; 
 struct fb_cmap const default_4_colors ; 
 struct fb_cmap const default_8_colors ; 

const struct fb_cmap *fb_default_cmap(int len)
{
    if (len <= 2)
	return &default_2_colors;
    if (len <= 4)
	return &default_4_colors;
    if (len <= 8)
	return &default_8_colors;
    return &default_16_colors;
}
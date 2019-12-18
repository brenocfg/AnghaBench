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
 int s3c_fb_win_pal_size (unsigned int) ; 

__attribute__((used)) static int s3c_fb_win_has_palette(unsigned int win, unsigned int bpp)
{
	return s3c_fb_win_pal_size(win) <= (1 << bpp);
}
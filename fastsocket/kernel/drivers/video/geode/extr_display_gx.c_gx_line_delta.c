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

int gx_line_delta(int xres, int bpp)
{
	/* Must be a multiple of 8 bytes. */
	return (xres * (bpp >> 3) + 7) & ~0x7;
}
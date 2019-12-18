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
struct em28xx {int dummy; } ;

/* Variables and functions */
 unsigned int norm_maxh (struct em28xx*) ; 
 unsigned int norm_maxw (struct em28xx*) ; 

__attribute__((used)) static void get_scale(struct em28xx *dev,
			unsigned int width, unsigned int height,
			unsigned int *hscale, unsigned int *vscale)
{
	unsigned int          maxw = norm_maxw(dev);
	unsigned int          maxh = norm_maxh(dev);

	*hscale = (((unsigned long)maxw) << 12) / width - 4096L;
	if (*hscale >= 0x4000)
		*hscale = 0x3fff;

	*vscale = (((unsigned long)maxh) << 12) / height - 4096L;
	if (*vscale >= 0x4000)
		*vscale = 0x3fff;
}
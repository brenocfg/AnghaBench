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
struct TYPE_2__ {unsigned int width; int height; } ;
typedef  TYPE_1__ VIDEOMODE_resolution_t ;

/* Variables and functions */

__attribute__((used)) static int CompareResolutions(const void *res1, const void *res2)
{
	unsigned int w = ((const VIDEOMODE_resolution_t *)res1)->width - ((const VIDEOMODE_resolution_t *)res2)->width;
	if (w != 0)
		return w;
	return ((const VIDEOMODE_resolution_t *)res1)->height - ((const VIDEOMODE_resolution_t *)res2)->height;
}
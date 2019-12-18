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
struct pwc_device {size_t fill_image; scalar_t__* image_used; } ;

/* Variables and functions */
 int pwc_mbufs ; 

void pwc_next_image(struct pwc_device *pdev)
{
	pdev->image_used[pdev->fill_image] = 0;
	pdev->fill_image = (pdev->fill_image + 1) % pwc_mbufs;
}
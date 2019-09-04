#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int crop_x; unsigned int crop_y; unsigned int crop_w; unsigned int crop_h; } ;
typedef  TYPE_1__ zbar_image_t ;

/* Variables and functions */

void zbar_image_get_crop (const zbar_image_t *img,
                          unsigned *x,
                          unsigned *y,
                          unsigned *w,
                          unsigned *h)
{
    if(x) *x = img->crop_x;
    if(y) *y = img->crop_y;
    if(w) *w = img->crop_w;
    if(h) *h = img->crop_h;
}
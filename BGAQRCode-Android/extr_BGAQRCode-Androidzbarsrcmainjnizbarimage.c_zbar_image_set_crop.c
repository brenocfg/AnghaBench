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
struct TYPE_3__ {unsigned int width; unsigned int crop_x; unsigned int crop_w; unsigned int height; unsigned int crop_y; unsigned int crop_h; } ;
typedef  TYPE_1__ zbar_image_t ;

/* Variables and functions */

void zbar_image_set_crop (zbar_image_t *img,
                          unsigned x,
                          unsigned y,
                          unsigned w,
                          unsigned h)
{
    unsigned img_w = img->width;
    if(x > img_w) x = img_w;
    if(x + w > img_w) w = img_w - x;
    img->crop_x = x;
    img->crop_w = w;

    unsigned img_h = img->height;
    if(y > img_h) y = img_h;
    if(y + h > img_h) h = img_h - y;
    img->crop_y = y;
    img->crop_h = h;
}
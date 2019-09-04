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
struct TYPE_3__ {unsigned int width; unsigned int height; } ;
typedef  TYPE_1__ zbar_image_t ;

/* Variables and functions */

void zbar_image_get_size (const zbar_image_t *img,
                          unsigned *w,
                          unsigned *h)
{
    if(w) *w = img->width;
    if(h) *h = img->height;
}
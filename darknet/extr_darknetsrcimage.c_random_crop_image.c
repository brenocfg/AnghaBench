#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ h; scalar_t__ w; } ;
typedef  TYPE_1__ image ;

/* Variables and functions */
 TYPE_1__ crop_image (TYPE_1__,int,int,int,int) ; 
 int rand_int (int /*<<< orphan*/ ,scalar_t__) ; 

image random_crop_image(image im, int w, int h)
{
    int dx = rand_int(0, im.w - w);
    int dy = rand_int(0, im.h - h);
    image crop = crop_image(im, dx, dy, w, h);
    return crop;
}
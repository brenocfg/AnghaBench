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
struct TYPE_6__ {int w; int h; } ;
typedef  TYPE_1__ image ;

/* Variables and functions */
 TYPE_1__ resize_image (TYPE_1__,int,int) ; 

image resize_min(image im, int min)
{
    int w = im.w;
    int h = im.h;
    if(w < h){
        h = (h * min) / w;
        w = min;
    } else {
        w = (w * min) / h;
        h = min;
    }
    if(w == im.w && h == im.h) return im;
    image resized = resize_image(im, w, h);
    return resized;
}
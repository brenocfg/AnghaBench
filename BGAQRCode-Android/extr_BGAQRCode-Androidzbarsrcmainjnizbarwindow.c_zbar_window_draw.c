#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ src_width; scalar_t__ src_height; TYPE_2__* image; scalar_t__ dst_width; int /*<<< orphan*/  draw_image; } ;
typedef  TYPE_1__ zbar_window_t ;
struct TYPE_9__ {scalar_t__ width; scalar_t__ height; } ;
typedef  TYPE_2__ zbar_image_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_image_refcnt (TYPE_2__*,int) ; 
 scalar_t__ window_lock (TYPE_1__*) ; 
 int window_unlock (TYPE_1__*) ; 

int zbar_window_draw (zbar_window_t *w,
                      zbar_image_t *img)
{
    if(window_lock(w))
        return(-1);
    if(!w->draw_image)
        img = NULL;
    if(img) {
        _zbar_image_refcnt(img, 1);
        if(img->width != w->src_width ||
           img->height != w->src_height)
            w->dst_width = 0;
    }
    if(w->image)
        _zbar_image_refcnt(w->image, -1);
    w->image = img;
    return(window_unlock(w));
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ y; int /*<<< orphan*/  x; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_12__ {scalar_t__ height; int /*<<< orphan*/  xwin; int /*<<< orphan*/  display; int /*<<< orphan*/  width; TYPE_5__ scaled_size; TYPE_5__ scaled_offset; TYPE_4__* state; } ;
typedef  TYPE_2__ zbar_window_t ;
struct TYPE_13__ {scalar_t__ data; } ;
typedef  TYPE_3__ zbar_image_t ;
struct TYPE_11__ {TYPE_6__* x; } ;
struct TYPE_14__ {int /*<<< orphan*/  gc; TYPE_1__ img; } ;
typedef  TYPE_4__ window_state_t ;
typedef  TYPE_5__ point_t ;
struct TYPE_16__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_6__ XImage ;

/* Variables and functions */
 int /*<<< orphan*/  XPutImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  assert (TYPE_6__*) ; 

__attribute__((used)) static int ximage_draw (zbar_window_t *w,
                        zbar_image_t *img)
{
    window_state_t *x = w->state;
    XImage *ximg = x->img.x;
    assert(ximg);
    ximg->data = (void*)img->data;

    point_t src = { 0, 0 };
    point_t dst = w->scaled_offset;
    if(dst.x < 0) {
        src.x = -dst.x;
        dst.x = 0;
    }
    if(dst.y < 0) {
        src.y = -dst.y;
        dst.y = 0;
    }
    point_t size = w->scaled_size;
    if(size.x > w->width)
        size.x = w->width;
    if(size.y > w->height)
        size.y = w->height;

    XPutImage(w->display, w->xwin, x->gc, ximg,
              src.x, src.y, dst.x, dst.y, size.x, size.y);
    ximg->data = NULL;
    return(0);
}
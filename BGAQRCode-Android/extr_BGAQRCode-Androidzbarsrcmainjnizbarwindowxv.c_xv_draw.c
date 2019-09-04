#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_13__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_15__ {TYPE_3__ scaled_size; TYPE_2__ scaled_offset; int /*<<< orphan*/  src_height; int /*<<< orphan*/  src_width; int /*<<< orphan*/  xwin; int /*<<< orphan*/  display; TYPE_6__* state; } ;
typedef  TYPE_4__ zbar_window_t ;
struct TYPE_16__ {int /*<<< orphan*/  datalen; scalar_t__ data; } ;
typedef  TYPE_5__ zbar_image_t ;
struct TYPE_12__ {TYPE_7__* xv; } ;
struct TYPE_17__ {int /*<<< orphan*/  gc; int /*<<< orphan*/  img_port; TYPE_1__ img; } ;
typedef  TYPE_6__ window_state_t ;
struct TYPE_18__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_7__ XvImage ;

/* Variables and functions */
 int /*<<< orphan*/  XvPutImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_7__*) ; 
 int /*<<< orphan*/  zprintf (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xv_draw (zbar_window_t *w,
                    zbar_image_t *img)
{
    window_state_t *x = w->state;
    XvImage *xvimg = x->img.xv;
    assert(xvimg);
    xvimg->data = (void*)img->data;
    zprintf(24, "XvPutImage(%dx%d -> %dx%d (%08lx))\n",
            w->src_width, w->src_height, w->scaled_size.x, w->scaled_size.y,
            img->datalen);
    XvPutImage(w->display, x->img_port, w->xwin, x->gc, xvimg,
               0, 0, w->src_width, w->src_height,
               w->scaled_offset.x, w->scaled_offset.y,
               w->scaled_size.x, w->scaled_size.y);
    xvimg->data = NULL;  /* FIXME hold shm image until completion */
    return(0);
}
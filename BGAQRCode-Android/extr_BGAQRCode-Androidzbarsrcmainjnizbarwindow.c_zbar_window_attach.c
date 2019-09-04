#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_8__ {int max_width; int max_height; int scale_num; int scale_den; scalar_t__ dst_height; scalar_t__ dst_width; TYPE_1__ scaled_size; scalar_t__ src_height; scalar_t__ src_width; scalar_t__ src_format; int /*<<< orphan*/ * formats; int /*<<< orphan*/ * draw_image; int /*<<< orphan*/  (* cleanup ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ zbar_window_t ;

/* Variables and functions */
 int _zbar_window_attach (TYPE_2__*,void*,unsigned long) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  zbar_window_draw (TYPE_2__*,int /*<<< orphan*/ *) ; 

int zbar_window_attach (zbar_window_t *w,
                        void *display,
                        unsigned long drawable)
{
    /* release image */
    zbar_window_draw(w, NULL);
    if(w->cleanup) {
        w->cleanup(w);
        w->cleanup = NULL;
        w->draw_image = NULL;
    }
    if(w->formats) {
        free(w->formats);
        w->formats = NULL;
    }
    w->src_format = 0;
    w->src_width = w->src_height = 0;
    w->scaled_size.x = w->scaled_size.y = 0;
    w->dst_width = w->dst_height = 0;
    w->max_width = w->max_height = 1 << 15;
    w->scale_num = w->scale_den = 1;
    return(_zbar_window_attach(w, display, drawable));
}
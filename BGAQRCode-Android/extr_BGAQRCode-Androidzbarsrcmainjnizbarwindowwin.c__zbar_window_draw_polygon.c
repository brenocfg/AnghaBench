#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_12__ {TYPE_3__ scaled_offset; TYPE_1__* state; } ;
typedef  TYPE_2__ zbar_window_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  TYPE_3__ point_t ;
struct TYPE_14__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_11__ {int /*<<< orphan*/  hdc; } ;
typedef  TYPE_4__ POINT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  Polyline (int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 int /*<<< orphan*/  win_set_rgb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ window_scale_pt (TYPE_2__*,TYPE_3__ const) ; 

int _zbar_window_draw_polygon (zbar_window_t *w,
                               uint32_t rgb,
                               const point_t *pts,
                               int npts)
{
    HDC hdc = w->state->hdc;
    win_set_rgb(hdc, rgb);

    point_t org = w->scaled_offset;
    POINT gdipts[npts + 1];
    int i;
    for(i = 0; i < npts; i++) {
        point_t p = window_scale_pt(w, pts[i]);
        gdipts[i].x = p.x + org.x;
        gdipts[i].y = p.y + org.y;
    }
    gdipts[npts] = gdipts[0];

    Polyline(hdc, gdipts, npts + 1);
    return(0);
}
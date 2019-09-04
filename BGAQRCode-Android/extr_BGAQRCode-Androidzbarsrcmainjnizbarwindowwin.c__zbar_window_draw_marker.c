#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* state; } ;
typedef  TYPE_2__ zbar_window_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_10__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_3__ point_t ;
struct TYPE_11__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {int /*<<< orphan*/  hdc; } ;
typedef  TYPE_4__ POINT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  PolyPolyline (int /*<<< orphan*/ ,TYPE_4__*,int const*,int) ; 
 int /*<<< orphan*/  win_set_rgb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int _zbar_window_draw_marker (zbar_window_t *w,
                              uint32_t rgb,
                              point_t p)
{
    HDC hdc = w->state->hdc;
    win_set_rgb(hdc, rgb);

    static const DWORD npolys[3] = { 5, 2, 2 };
    POINT polys[9] = {
        { p.x - 2, p.y - 2 },
        { p.x - 2, p.y + 2 },
        { p.x + 2, p.y + 2 },
        { p.x + 2, p.y - 2 },
        { p.x - 2, p.y - 2 },

        { p.x - 3, p.y },
        { p.x + 4, p.y },

        { p.x, p.y - 3 },
        { p.x, p.y + 4 },
    };

    PolyPolyline(hdc, polys, npolys, 3);
    return(0);
}
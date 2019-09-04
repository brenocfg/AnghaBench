#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_2__* state; } ;
typedef  TYPE_1__ zbar_window_t ;
struct TYPE_5__ {int /*<<< orphan*/  logo_z; int /*<<< orphan*/  logo_zbpen; int /*<<< orphan*/  logo_zbars; int /*<<< orphan*/  logo_zpen; int /*<<< orphan*/  hdc; } ;
typedef  TYPE_2__ window_state_t ;
typedef  int /*<<< orphan*/  HRGN ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  BLACK_BRUSH ; 
 int /*<<< orphan*/  CombineRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateRectRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExtSelectClipRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FillRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Polyline (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RGN_AND ; 
 int /*<<< orphan*/  RGN_DIFF ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WHITE_BRUSH ; 

int _zbar_window_draw_logo (zbar_window_t *w)
{
    HDC hdc = w->state->hdc;

    window_state_t *win = w->state;

    /* FIXME buffer offscreen */
    HRGN rgn = CreateRectRgn(0, 0, w->width, w->height);
    CombineRgn(rgn, rgn, win->logo_zbars, RGN_DIFF);
    FillRgn(hdc, rgn, GetStockObject(WHITE_BRUSH));
    DeleteObject(rgn);

    FillRgn(hdc, win->logo_zbars, GetStockObject(BLACK_BRUSH));

    SelectObject(hdc, win->logo_zpen);
    Polyline(hdc, win->logo_z, 4);

    ExtSelectClipRgn(hdc, win->logo_zbars, RGN_AND);
    SelectObject(hdc, win->logo_zbpen);
    Polyline(hdc, win->logo_z, 4);
    return(0);
}
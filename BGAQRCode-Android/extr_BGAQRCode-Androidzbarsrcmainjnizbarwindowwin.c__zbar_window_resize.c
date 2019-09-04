#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int height; int width; TYPE_3__* state; } ;
typedef  TYPE_2__ zbar_window_t ;
struct TYPE_9__ {int logo_scale; TYPE_1__* logo_z; int /*<<< orphan*/ * logo_zbars; int /*<<< orphan*/ * logo_zbpen; int /*<<< orphan*/ * logo_zpen; } ;
typedef  TYPE_3__ window_state_t ;
struct TYPE_10__ {void* lbColor; int /*<<< orphan*/  lbStyle; int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {int x; int y; } ;
typedef  TYPE_4__ LOGBRUSH ;
typedef  int /*<<< orphan*/ * HRGN ;

/* Variables and functions */
 int /*<<< orphan*/  BS_SOLID ; 
 int /*<<< orphan*/  CombineRgn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateRectRgn (int,int,int,int) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 void* ExtCreatePen (int,int,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int PS_ENDCAP_ROUND ; 
 int PS_GEOMETRIC ; 
 int PS_JOIN_ROUND ; 
 int PS_SOLID ; 
 void* RGB (int,int,int) ; 
 int /*<<< orphan*/  RGN_OR ; 
 int /*<<< orphan*/  zprintf (int,char*,int,int,int) ; 

int _zbar_window_resize (zbar_window_t *w)
{
    window_state_t *win = w->state;
    int lbw;
    if(w->height * 8 / 10 <= w->width)
        lbw = w->height / 36;
    else
        lbw = w->width * 5 / 144;
    if(lbw < 1)
        lbw = 1;
    win->logo_scale = lbw;
    zprintf(7, "%dx%d scale=%d\n", w->width, w->height, lbw);
    if(win->logo_zbars) {
        DeleteObject(win->logo_zbars);
        win->logo_zbars = NULL;
    }
    if(win->logo_zpen)
        DeleteObject(win->logo_zpen);
    if(win->logo_zbpen)
        DeleteObject(win->logo_zbpen);

    LOGBRUSH lb = { 0, };
    lb.lbStyle = BS_SOLID;
    lb.lbColor = RGB(0xd7, 0x33, 0x33);
    win->logo_zpen = ExtCreatePen(PS_GEOMETRIC | PS_SOLID |
                                  PS_ENDCAP_ROUND | PS_JOIN_ROUND,
                                  lbw * 2, &lb, 0, NULL);

    lb.lbColor = RGB(0xa4, 0x00, 0x00);
    win->logo_zbpen = ExtCreatePen(PS_GEOMETRIC | PS_SOLID |
                                   PS_ENDCAP_ROUND | PS_JOIN_ROUND,
                                   lbw * 2, &lb, 0, NULL);

    int x0 = w->width / 2;
    int y0 = w->height / 2;
    int by0 = y0 - 54 * lbw / 5;
    int bh = 108 * lbw / 5;

    static const int bx[5] = { -6, -3, -1,  2,  5 };
    static const int bw[5] = {  1,  1,  2,  2,  1 };

    int i;
    for(i = 0; i < 5; i++) {
        int x = x0 + lbw * bx[i];
        HRGN bar = CreateRectRgn(x, by0,
                                 x + lbw * bw[i], by0 + bh);
        if(win->logo_zbars) {
            CombineRgn(win->logo_zbars, win->logo_zbars, bar, RGN_OR);
            DeleteObject(bar);
        }
        else
            win->logo_zbars = bar;
    }

    static const int zx[4] = { -7,  7, -7,  7 };
    static const int zy[4] = { -8, -8,  8,  8 };

    for(i = 0; i < 4; i++) {
        win->logo_z[i].x = x0 + lbw * zx[i];
        win->logo_z[i].y = y0 + lbw * zy[i];
    }
    return(0);
}
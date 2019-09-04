#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int height; TYPE_1__* state; scalar_t__ width; } ;
typedef  TYPE_2__ zbar_window_t ;
typedef  int uint32_t ;
struct TYPE_8__ {int y; int /*<<< orphan*/  x; } ;
typedef  TYPE_3__ point_t ;
struct TYPE_6__ {int font_height; int /*<<< orphan*/  hdc; } ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  RGB (int,int,int) ; 
 int /*<<< orphan*/  SetBkMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTextAlign (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TA_BASELINE ; 
 int TA_CENTER ; 
 int TA_RIGHT ; 
 int /*<<< orphan*/  TRANSPARENT ; 
 int /*<<< orphan*/  TextOut (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char const*,int) ; 
 scalar_t__ isprint (char const) ; 

int _zbar_window_draw_text (zbar_window_t *w,
                            uint32_t rgb,
                            point_t p,
                            const char *text)
{
    HDC hdc = w->state->hdc;
    SetTextColor(hdc, RGB((rgb & 4) * 0x33,
                          (rgb & 2) * 0x66,
                          (rgb & 1) * 0xcc));
    SetBkMode(hdc, TRANSPARENT);

    int n = 0;
    while(n < 32 && text[n] && isprint(text[n]))
        n++;

    if(p.x >= 0)
        SetTextAlign(hdc, TA_BASELINE | TA_CENTER);
    else {
        SetTextAlign(hdc, TA_BASELINE | TA_RIGHT);
        p.x += w->width;
    }

    if(p.y < 0)
        p.y = w->height + p.y * w->state->font_height * 5 / 4;

    TextOut(hdc, p.x, p.y, text, n);
    return(0);
}
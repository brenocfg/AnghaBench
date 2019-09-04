#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * display; TYPE_3__* state; } ;
typedef  TYPE_2__ zbar_window_t ;
struct TYPE_10__ {int biSize; int biPlanes; long biXPelsPerMeter; long biYPelsPerMeter; } ;
struct TYPE_12__ {int /*<<< orphan*/  font_height; TYPE_1__ bih; } ;
typedef  TYPE_3__ window_state_t ;
struct TYPE_13__ {int /*<<< orphan*/  tmHeight; } ;
typedef  TYPE_4__ TEXTMETRIC ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  ANSI_CHARSET ; 
 int /*<<< orphan*/  CreateFontW (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int FF_MODERN ; 
 int FIXED_PITCH ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ *) ; 
 long GetDeviceCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTextMetrics (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  HORZRES ; 
 int /*<<< orphan*/  HORZSIZE ; 
 int /*<<< orphan*/  LOGPIXELSY ; 
 int MulDiv (int,long,int) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERTRES ; 
 int /*<<< orphan*/  VERTSIZE ; 
 int _zbar_window_dib_init (TYPE_2__*) ; 
 TYPE_3__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 

int _zbar_window_attach (zbar_window_t *w,
                         void *display,
                         unsigned long unused)
{
    window_state_t *win = w->state;
    if(w->display) {
        /* FIXME cleanup existing resources */
        w->display = NULL;
    }

    if(!display) {
        if(win) {
            free(win);
            w->state = NULL;
        }
        return(0);
    }

    if(!win)
        win = w->state = calloc(1, sizeof(window_state_t));

    w->display = display;

    win->bih.biSize = sizeof(win->bih);
    win->bih.biPlanes = 1;

    HDC hdc = GetDC(w->display);
    if(!hdc)
        return(-1/*FIXME*/);
    win->bih.biXPelsPerMeter =
        1000L * GetDeviceCaps(hdc, HORZRES) / GetDeviceCaps(hdc, HORZSIZE);
    win->bih.biYPelsPerMeter =
        1000L * GetDeviceCaps(hdc, VERTRES) / GetDeviceCaps(hdc, VERTSIZE);

    int height = -MulDiv(11, GetDeviceCaps(hdc, LOGPIXELSY), 96);
    HFONT font = CreateFontW(height, 0, 0, 0, 0, 0, 0, 0,
                             ANSI_CHARSET, 0, 0, 0,
                             FF_MODERN | FIXED_PITCH, NULL);

    SelectObject(hdc, font);
    DeleteObject(font);

    TEXTMETRIC tm;
    GetTextMetrics(hdc, &tm);
    win->font_height = tm.tmHeight;

    ReleaseDC(w->display, hdc);

    return(_zbar_window_dib_init(w));
}
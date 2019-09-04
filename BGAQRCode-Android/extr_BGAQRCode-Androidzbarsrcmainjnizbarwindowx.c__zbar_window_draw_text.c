#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int width; scalar_t__ height; int /*<<< orphan*/  xwin; int /*<<< orphan*/  display; TYPE_2__* state; } ;
typedef  TYPE_1__ zbar_window_t ;
struct TYPE_8__ {int /*<<< orphan*/  gc; TYPE_6__* font; int /*<<< orphan*/ * colors; } ;
typedef  TYPE_2__ window_state_t ;
typedef  size_t uint32_t ;
struct TYPE_9__ {int x; scalar_t__ y; } ;
typedef  TYPE_3__ point_t ;
struct TYPE_10__ {int ascent; int descent; } ;

/* Variables and functions */
 int /*<<< orphan*/  XDrawString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char const*,int) ; 
 int /*<<< orphan*/  XSetForeground (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int XTextWidth (TYPE_6__*,char const*,int) ; 
 scalar_t__ isprint (char const) ; 

int _zbar_window_draw_text (zbar_window_t *w,
                            uint32_t rgb,
                            point_t p,
                            const char *text)
{
    window_state_t *xs = w->state;
    if(!xs->font)
        return(-1);

    XSetForeground(w->display, xs->gc, xs->colors[rgb]);

    int n = 0;
    while(n < 32 && text[n] && isprint(text[n]))
        n++;

    int width = XTextWidth(xs->font, text, n);
    if(p.x >= 0)
        p.x -= width / 2;
    else
        p.x += w->width - width;

    int dy = xs->font->ascent + xs->font->descent;
    if(p.y >= 0)
        p.y -= dy / 2;
    else
        p.y = w->height + p.y * dy * 5 / 4;

    XDrawString(w->display, w->xwin, xs->gc, p.x, p.y, text, n);
    return(0);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int x; int y; int member_0; int member_1; } ;
struct TYPE_17__ {int overlay; int width; int height; long time; int time_avg; TYPE_5__ scaled_offset; TYPE_2__* image; } ;
typedef  TYPE_3__ zbar_window_t ;
struct TYPE_18__ {scalar_t__ cache_count; scalar_t__ type; int npts; int /*<<< orphan*/ * pts; struct TYPE_18__* next; } ;
typedef  TYPE_4__ zbar_symbol_t ;
typedef  int uint32_t ;
typedef  TYPE_5__ point_t ;
struct TYPE_16__ {TYPE_1__* syms; } ;
struct TYPE_15__ {TYPE_4__* head; } ;

/* Variables and functions */
 scalar_t__ ZBAR_QRCODE ; 
 unsigned long _zbar_timer_now () ; 
 int /*<<< orphan*/  _zbar_window_draw_marker (TYPE_3__*,int,TYPE_5__) ; 
 int /*<<< orphan*/  _zbar_window_draw_text (TYPE_3__*,int,TYPE_5__,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 
 int /*<<< orphan*/  window_outline_symbol (TYPE_3__*,int,TYPE_4__ const*) ; 
 TYPE_5__ window_scale_pt (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int window_draw_overlay (zbar_window_t *w)
{
    if(!w->overlay)
        return(0);
    if(w->overlay >= 1 && w->image && w->image->syms) {
        /* FIXME outline each symbol */
        const zbar_symbol_t *sym = w->image->syms->head;
        for(; sym; sym = sym->next) {
            uint32_t color = ((sym->cache_count < 0) ? 4 : 2);
            if(sym->type == ZBAR_QRCODE)
                window_outline_symbol(w, color, sym);
            else {
                /* FIXME linear bbox broken */
                point_t org = w->scaled_offset;
                int i;
                for(i = 0; i < sym->npts; i++) {
                    point_t p = window_scale_pt(w, sym->pts[i]);
                    p.x += org.x;
                    p.y += org.y;
                    if(p.x < 3)
                        p.x = 3;
                    else if(p.x > w->width - 4)
                        p.x = w->width - 4;
                    if(p.y < 3)
                        p.y = 3;
                    else if(p.y > w->height - 4)
                        p.y = w->height - 4;
                    _zbar_window_draw_marker(w, color, p);
                }
            }
        }
    }

    if(w->overlay >= 2) {
        /* calculate/display frame rate */
        unsigned long time = _zbar_timer_now();
        if(w->time) {
            int avg = w->time_avg = (w->time_avg + time - w->time) / 2;
            point_t p = { -8, -1 };
            char text[32];
            sprintf(text, "%d.%01d fps", 1000 / avg, (10000 / avg) % 10);
            _zbar_window_draw_text(w, 3, p, text);
        }
        w->time = time;
    }
    return(0);
}
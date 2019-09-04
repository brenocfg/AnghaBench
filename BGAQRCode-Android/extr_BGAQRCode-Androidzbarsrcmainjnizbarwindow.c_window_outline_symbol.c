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
typedef  int /*<<< orphan*/  zbar_window_t ;
struct TYPE_5__ {int /*<<< orphan*/  npts; int /*<<< orphan*/  pts; struct TYPE_5__* next; TYPE_1__* syms; } ;
typedef  TYPE_2__ zbar_symbol_t ;
typedef  int uint32_t ;
struct TYPE_4__ {TYPE_2__* head; } ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_window_draw_polygon (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void window_outline_symbol (zbar_window_t *w,
                                   uint32_t color,
                                   const zbar_symbol_t *sym)
{
    if(sym->syms) {
        const zbar_symbol_t *s;
        for(s = sym->syms->head; s; s = s->next)
            window_outline_symbol(w, 1, s);
    }
    _zbar_window_draw_polygon(w, color, sym->pts, sym->npts);
}
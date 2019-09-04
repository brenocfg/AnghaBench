#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  display; TYPE_2__* state; } ;
typedef  TYPE_1__ zbar_window_t ;
struct TYPE_6__ {void** logo_colors; void** colors; } ;
typedef  TYPE_2__ window_state_t ;
typedef  int /*<<< orphan*/  Colormap ;

/* Variables and functions */
 int /*<<< orphan*/  DefaultColormap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DefaultScreen (int /*<<< orphan*/ ) ; 
 void* window_alloc_color (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static inline int window_alloc_colors (zbar_window_t *w)
{
    window_state_t *x = w->state;
    Colormap cmap = DefaultColormap(w->display, DefaultScreen(w->display));
    int i;
    for(i = 0; i < 8; i++)
        x->colors[i] = window_alloc_color(w, cmap,
                                          (i & 4) ? (0xcc * 0x101) : 0,
                                          (i & 2) ? (0xcc * 0x101) : 0,
                                          (i & 1) ? (0xcc * 0x101) : 0);

    x->logo_colors[0] = window_alloc_color(w, cmap, 0xd709, 0x3333, 0x3333);
    x->logo_colors[1] = window_alloc_color(w, cmap, 0xa3d6, 0x0000, 0x0000);
    return(0);
}
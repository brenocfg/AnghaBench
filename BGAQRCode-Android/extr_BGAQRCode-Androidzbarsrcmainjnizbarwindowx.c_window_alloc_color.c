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
struct TYPE_5__ {int /*<<< orphan*/  display; } ;
typedef  TYPE_1__ zbar_window_t ;
struct TYPE_6__ {unsigned short red; unsigned short green; unsigned short blue; unsigned long pixel; scalar_t__ flags; } ;
typedef  TYPE_2__ XColor ;
typedef  int /*<<< orphan*/  Colormap ;

/* Variables and functions */
 int /*<<< orphan*/  XAllocColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static inline unsigned long window_alloc_color (zbar_window_t *w,
                                                Colormap cmap,
                                                unsigned short r,
                                                unsigned short g,
                                                unsigned short b)
{
    XColor color;
    color.red = r;
    color.green = g;
    color.blue = b;
    color.flags = 0;
    XAllocColor(w->display, cmap, &color);
    return(color.pixel);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int y; int thickness; int h; int x; int w; } ;
typedef  TYPE_1__ DrawBoxContext ;

/* Variables and functions */

int pixel_belongs_to_box(DrawBoxContext *s, int x, int y)
{
    return (y - s->y < s->thickness) || (s->y + s->h - 1 - y < s->thickness) ||
           (x - s->x < s->thickness) || (s->x + s->w - 1 - x < s->thickness);
}
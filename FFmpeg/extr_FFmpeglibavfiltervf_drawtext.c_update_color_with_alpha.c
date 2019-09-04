#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int alpha; int /*<<< orphan*/  dc; } ;
struct TYPE_7__ {int* rgba; } ;
typedef  TYPE_1__ FFDrawColor ;
typedef  TYPE_2__ DrawTextContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_draw_color (int /*<<< orphan*/ *,TYPE_1__*,int*) ; 

__attribute__((used)) static void update_color_with_alpha(DrawTextContext *s, FFDrawColor *color, const FFDrawColor incolor)
{
    *color = incolor;
    color->rgba[3] = (color->rgba[3] * s->alpha) / 255;
    ff_draw_color(&s->dc, color, color->rgba);
}
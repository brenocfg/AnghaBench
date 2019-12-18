#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int* rgba; TYPE_3__* comp; } ;
struct TYPE_12__ {int nb_planes; TYPE_2__* desc; } ;
struct TYPE_11__ {unsigned int* u16; } ;
struct TYPE_10__ {TYPE_1__* comp; } ;
struct TYPE_9__ {int depth; } ;
typedef  TYPE_4__ FFDrawContext ;
typedef  TYPE_5__ FFDrawColor ;

/* Variables and functions */

__attribute__((used)) static void reverse_color16(FFDrawContext *draw, FFDrawColor *color, FFDrawColor *reverse)
{
    int p;

    reverse->rgba[3] = 255;
    for (p = 0; p < draw->nb_planes; p++) {
        const unsigned max = (1 << draw->desc->comp[p].depth) - 1;
        const unsigned mid = (max + 1) / 2;

        reverse->comp[p].u16[0] = color->comp[p].u16[0] > mid ? 0 : max;
        reverse->comp[p].u16[1] = color->comp[p].u16[1] > mid ? 0 : max;
        reverse->comp[p].u16[2] = color->comp[p].u16[2] > mid ? 0 : max;
    }
}
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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_13__ {TYPE_3__* comp; } ;
struct TYPE_12__ {int nb_planes; int* pixelstep; TYPE_2__* desc; int /*<<< orphan*/ * vsub; int /*<<< orphan*/ * hsub; } ;
struct TYPE_11__ {int /*<<< orphan*/ * u8; int /*<<< orphan*/ * u16; } ;
struct TYPE_10__ {TYPE_1__* comp; } ;
struct TYPE_9__ {int depth; } ;
typedef  TYPE_4__ FFDrawContext ;
typedef  TYPE_5__ FFDrawColor ;

/* Variables and functions */
 int AV_CEIL_RSHIFT (int,int /*<<< orphan*/ ) ; 
 scalar_t__ HAVE_BIGENDIAN ; 
 int /*<<< orphan*/  av_bswap16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pointer_at (TYPE_4__*,int /*<<< orphan*/ **,int*,int,int,int) ; 

void ff_fill_rectangle(FFDrawContext *draw, FFDrawColor *color,
                       uint8_t *dst[], int dst_linesize[],
                       int dst_x, int dst_y, int w, int h)
{
    int plane, x, y, wp, hp;
    uint8_t *p0, *p;
    FFDrawColor color_tmp = *color;

    for (plane = 0; plane < draw->nb_planes; plane++) {
        p0 = pointer_at(draw, dst, dst_linesize, plane, dst_x, dst_y);
        wp = AV_CEIL_RSHIFT(w, draw->hsub[plane]);
        hp = AV_CEIL_RSHIFT(h, draw->vsub[plane]);
        if (!hp)
            return;
        p = p0;

        if (HAVE_BIGENDIAN && draw->desc->comp[0].depth > 8) {
            for (x = 0; 2*x < draw->pixelstep[plane]; x++)
                color_tmp.comp[plane].u16[x] = av_bswap16(color_tmp.comp[plane].u16[x]);
        }

        /* copy first line from color */
        for (x = 0; x < wp; x++) {
            memcpy(p, color_tmp.comp[plane].u8, draw->pixelstep[plane]);
            p += draw->pixelstep[plane];
        }
        wp *= draw->pixelstep[plane];
        /* copy next lines from first line */
        p = p0 + dst_linesize[plane];
        for (y = 1; y < hp; y++) {
            memcpy(p, p0, wp);
            p += dst_linesize[plane];
        }
    }
}
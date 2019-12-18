#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int nb_planes; int* pixelstep; int /*<<< orphan*/ * vsub; int /*<<< orphan*/ * hsub; } ;
typedef  TYPE_1__ FFDrawContext ;

/* Variables and functions */
 int AV_CEIL_RSHIFT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pointer_at (TYPE_1__*,int /*<<< orphan*/ **,int*,int,int,int) ; 

void ff_copy_rectangle2(FFDrawContext *draw,
                        uint8_t *dst[], int dst_linesize[],
                        uint8_t *src[], int src_linesize[],
                        int dst_x, int dst_y, int src_x, int src_y,
                        int w, int h)
{
    int plane, y, wp, hp;
    uint8_t *p, *q;

    for (plane = 0; plane < draw->nb_planes; plane++) {
        p = pointer_at(draw, src, src_linesize, plane, src_x, src_y);
        q = pointer_at(draw, dst, dst_linesize, plane, dst_x, dst_y);
        wp = AV_CEIL_RSHIFT(w, draw->hsub[plane]) * draw->pixelstep[plane];
        hp = AV_CEIL_RSHIFT(h, draw->vsub[plane]);
        for (y = 0; y < hp; y++) {
            memcpy(q, p, wp);
            p += src_linesize[plane];
            q += dst_linesize[plane];
        }
    }
}
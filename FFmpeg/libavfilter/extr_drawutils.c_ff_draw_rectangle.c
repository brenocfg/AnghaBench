#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int AV_CEIL_RSHIFT (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void ff_draw_rectangle(uint8_t *dst[4], int dst_linesize[4],
                       uint8_t *src[4], int pixelstep[4],
                       int hsub, int vsub, int x, int y, int w, int h)
{
    int i, plane;
    uint8_t *p;

    for (plane = 0; plane < 4 && dst[plane]; plane++) {
        int hsub1 = plane == 1 || plane == 2 ? hsub : 0;
        int vsub1 = plane == 1 || plane == 2 ? vsub : 0;
        int width  = AV_CEIL_RSHIFT(w, hsub1);
        int height = AV_CEIL_RSHIFT(h, vsub1);

        p = dst[plane] + (y >> vsub1) * dst_linesize[plane];
        for (i = 0; i < height; i++) {
            memcpy(p + (x >> hsub1) * pixelstep[plane],
                   src[plane], width * pixelstep[plane]);
            p += dst_linesize[plane];
        }
    }
}
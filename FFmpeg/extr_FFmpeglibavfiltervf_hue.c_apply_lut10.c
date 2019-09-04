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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/ ** lut_v10; int /*<<< orphan*/ ** lut_u10; } ;
typedef  TYPE_1__ HueContext ;

/* Variables and functions */
 int av_clip_uintp2 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void apply_lut10(HueContext *s,
                      uint16_t *udst, uint16_t *vdst, const int dst_linesize,
                      uint16_t *usrc, uint16_t *vsrc, const int src_linesize,
                      int w, int h)
{
    int i;

    while (h--) {
        for (i = 0; i < w; i++) {
            const int u = av_clip_uintp2(usrc[i], 10);
            const int v = av_clip_uintp2(vsrc[i], 10);

            udst[i] = s->lut_u10[u][v];
            vdst[i] = s->lut_v10[u][v];
        }

        usrc += src_linesize;
        vsrc += src_linesize;
        udst += dst_linesize;
        vdst += dst_linesize;
    }
}
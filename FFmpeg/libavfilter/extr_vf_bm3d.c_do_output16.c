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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {int* planeheight; int* planewidth; int depth; TYPE_1__* slices; } ;
struct TYPE_4__ {float* num; float* den; } ;
typedef  TYPE_1__ SliceContext ;
typedef  TYPE_2__ BM3DContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_clip_uintp2_c (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  lrintf (float) ; 

__attribute__((used)) static void do_output16(BM3DContext *s, uint8_t *dst, int dst_linesize,
                        int plane, int nb_jobs)
{
    const int height = s->planeheight[plane];
    const int width = s->planewidth[plane];
    const int depth = s->depth;
    int i, j, k;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            uint16_t *dstp = (uint16_t *)dst + i * dst_linesize / 2;
            float sum_den = 0.f;
            float sum_num = 0.f;

            for (k = 0; k < nb_jobs; k++) {
                SliceContext *sc = &s->slices[k];
                float num = sc->num[i * width + j];
                float den = sc->den[i * width + j];

                sum_num += num;
                sum_den += den;
            }

            dstp[j] = av_clip_uintp2_c(lrintf(sum_num / sum_den), depth);
        }
    }
}
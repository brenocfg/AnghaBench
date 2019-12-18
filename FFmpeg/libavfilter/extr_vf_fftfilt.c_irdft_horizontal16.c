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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {int* linesize; scalar_t__* data; } ;
struct TYPE_5__ {int depth; int** rdft_hdata; int* rdft_hlen; int* rdft_vlen; int /*<<< orphan*/ * ihrdft; } ;
typedef  TYPE_1__ FFTFILTContext ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  av_clip (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_rdft_calc (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void irdft_horizontal16(FFTFILTContext *s, AVFrame *out, int w, int h, int plane)
{
    uint16_t *dst = (uint16_t *)out->data[plane];
    int linesize = out->linesize[plane] / 2;
    int max = (1 << s->depth) - 1;
    int i, j;

    for (i = 0; i < h; i++)
        av_rdft_calc(s->ihrdft[plane], s->rdft_hdata[plane] + i * s->rdft_hlen[plane]);

    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            *(dst + linesize * i + j) = av_clip(s->rdft_hdata[plane][i
                                                *s->rdft_hlen[plane] + j] * 4 /
                                                (s->rdft_hlen[plane] *
                                                s->rdft_vlen[plane]), 0, max);
}
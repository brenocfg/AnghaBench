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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int width; int* subsampling; int height; } ;
typedef  TYPE_1__ TiffEncoderContext ;
struct TYPE_6__ {int* linesize; int /*<<< orphan*/ ** data; } ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 size_t FFMIN (int,int) ; 

__attribute__((used)) static void pack_yuv(TiffEncoderContext *s, const AVFrame *p,
                     uint8_t *dst, int lnum)
{
    int i, j, k;
    int w       = (s->width - 1) / s->subsampling[0] + 1;
    uint8_t *pu = &p->data[1][lnum / s->subsampling[1] * p->linesize[1]];
    uint8_t *pv = &p->data[2][lnum / s->subsampling[1] * p->linesize[2]];
    if (s->width % s->subsampling[0] || s->height % s->subsampling[1]) {
        for (i = 0; i < w; i++) {
            for (j = 0; j < s->subsampling[1]; j++)
                for (k = 0; k < s->subsampling[0]; k++)
                    *dst++ = p->data[0][FFMIN(lnum + j, s->height-1) * p->linesize[0] +
                                        FFMIN(i * s->subsampling[0] + k, s->width-1)];
            *dst++ = *pu++;
            *dst++ = *pv++;
        }
    }else{
        for (i = 0; i < w; i++) {
            for (j = 0; j < s->subsampling[1]; j++)
                for (k = 0; k < s->subsampling[0]; k++)
                    *dst++ = p->data[0][(lnum + j) * p->linesize[0] +
                                        i * s->subsampling[0] + k];
            *dst++ = *pu++;
            *dst++ = *pv++;
        }
    }
}
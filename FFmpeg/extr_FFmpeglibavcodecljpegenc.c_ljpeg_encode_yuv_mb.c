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
typedef  int uint8_t ;
struct TYPE_6__ {int* linesize; int** data; } ;
struct TYPE_5__ {int* hsample; int* vsample; int /*<<< orphan*/  huff_code_dc_chrominance; int /*<<< orphan*/  huff_size_dc_chrominance; int /*<<< orphan*/  huff_code_dc_luminance; int /*<<< orphan*/  huff_size_dc_luminance; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_1__ LJpegEncContext ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  PREDICT (int,int,int,int,int) ; 
 int /*<<< orphan*/  ff_mjpeg_encode_dc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ljpeg_encode_yuv_mb(LJpegEncContext *s, PutBitContext *pb,
                                       const AVFrame *frame, int predictor,
                                       int mb_x, int mb_y)
{
    int i;

    if (mb_x == 0 || mb_y == 0) {
        for (i = 0; i < 3; i++) {
            uint8_t *ptr;
            int x, y, h, v, linesize;
            h = s->hsample[i];
            v = s->vsample[i];
            linesize = frame->linesize[i];

            for (y = 0; y < v; y++) {
                for (x = 0; x < h; x++) {
                    int pred;

                    ptr = frame->data[i] + (linesize * (v * mb_y + y)) + (h * mb_x + x); //FIXME optimize this crap
                    if (y == 0 && mb_y == 0) {
                        if (x == 0 && mb_x == 0)
                            pred = 128;
                        else
                            pred = ptr[-1];
                    } else {
                        if (x == 0 && mb_x == 0) {
                            pred = ptr[-linesize];
                        } else {
                            PREDICT(pred, ptr[-linesize - 1], ptr[-linesize],
                                    ptr[-1], predictor);
                        }
                    }

                    if (i == 0)
                        ff_mjpeg_encode_dc(pb, *ptr - pred, s->huff_size_dc_luminance, s->huff_code_dc_luminance); //FIXME ugly
                    else
                        ff_mjpeg_encode_dc(pb, *ptr - pred, s->huff_size_dc_chrominance, s->huff_code_dc_chrominance);
                }
            }
        }
    } else {
        for (i = 0; i < 3; i++) {
            uint8_t *ptr;
            int x, y, h, v, linesize;
            h = s->hsample[i];
            v = s->vsample[i];
            linesize = frame->linesize[i];

            for (y = 0; y < v; y++) {
                for (x = 0; x < h; x++) {
                    int pred;

                    ptr = frame->data[i] + (linesize * (v * mb_y + y)) + (h * mb_x + x); //FIXME optimize this crap
                    PREDICT(pred, ptr[-linesize - 1], ptr[-linesize], ptr[-1], predictor);

                    if (i == 0)
                        ff_mjpeg_encode_dc(pb, *ptr - pred, s->huff_size_dc_luminance, s->huff_code_dc_luminance); //FIXME ugly
                    else
                        ff_mjpeg_encode_dc(pb, *ptr - pred, s->huff_size_dc_chrominance, s->huff_code_dc_chrominance);
                }
            }
        }
    }
}
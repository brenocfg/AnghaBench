#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_12__ {int height; int width; } ;
struct TYPE_11__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_10__ {int offset; } ;
struct TYPE_9__ {int stride; int crop_top; int crop_left; int slice_height; } ;
typedef  TYPE_1__ MediaCodecDecContext ;
typedef  TYPE_2__ FFAMediaCodecBufferInfo ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int FFALIGN (int,int) ; 
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void ff_mediacodec_sw_buffer_copy_yuv420_planar(AVCodecContext *avctx,
                                                MediaCodecDecContext *s,
                                                uint8_t *data,
                                                size_t size,
                                                FFAMediaCodecBufferInfo *info,
                                                AVFrame *frame)
{
    int i;
    uint8_t *src = NULL;

    for (i = 0; i < 3; i++) {
        int stride = s->stride;
        int height;

        src = data + info->offset;
        if (i == 0) {
            height = avctx->height;

            src += s->crop_top * s->stride;
            src += s->crop_left;
        } else {
            height = avctx->height / 2;
            stride = (s->stride + 1) / 2;

            src += s->slice_height * s->stride;

            if (i == 2) {
                src += ((s->slice_height + 1) / 2) * stride;
            }

            src += s->crop_top * stride;
            src += (s->crop_left / 2);
        }

        if (frame->linesize[i] == stride) {
            memcpy(frame->data[i], src, height * stride);
        } else {
            int j, width;
            uint8_t *dst = frame->data[i];

            if (i == 0) {
                width = avctx->width;
            } else if (i >= 1) {
                width = FFMIN(frame->linesize[i], FFALIGN(avctx->width, 2) / 2);
            }

            for (j = 0; j < height; j++) {
                memcpy(dst, src, width);
                src += stride;
                dst += frame->linesize[i];
            }
        }
    }
}
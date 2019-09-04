#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_8__ {int width; int height; TYPE_2__* priv_data; } ;
struct TYPE_7__ {int flags; TYPE_1__* last_frame; } ;
struct TYPE_6__ {scalar_t__** data; int* linesize; } ;
typedef  TYPE_2__ GIFContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int GF_OFFSETTING ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int,int,int,int,int,int) ; 
 scalar_t__ memcmp (scalar_t__ const*,scalar_t__ const*,int) ; 

__attribute__((used)) static void gif_crop_opaque(AVCodecContext *avctx,
                            const uint32_t *palette,
                            const uint8_t *buf, const int linesize,
                            int *width, int *height, int *x_start, int *y_start)
{
    GIFContext *s = avctx->priv_data;

    /* Crop image */
    if ((s->flags & GF_OFFSETTING) && s->last_frame && !palette) {
        const uint8_t *ref = s->last_frame->data[0];
        const int ref_linesize = s->last_frame->linesize[0];
        int x_end = avctx->width  - 1,
            y_end = avctx->height - 1;

        /* skip common lines */
        while (*y_start < y_end) {
            if (memcmp(ref + *y_start*ref_linesize, buf + *y_start*linesize, *width))
                break;
            (*y_start)++;
        }
        while (y_end > *y_start) {
            if (memcmp(ref + y_end*ref_linesize, buf + y_end*linesize, *width))
                break;
            y_end--;
        }
        *height = y_end + 1 - *y_start;

        /* skip common columns */
        while (*x_start < x_end) {
            int same_column = 1;
            for (int y = *y_start; y <= y_end; y++) {
                if (ref[y*ref_linesize + *x_start] != buf[y*linesize + *x_start]) {
                    same_column = 0;
                    break;
                }
            }
            if (!same_column)
                break;
            (*x_start)++;
        }
        while (x_end > *x_start) {
            int same_column = 1;
            for (int y = *y_start; y <= y_end; y++) {
                if (ref[y*ref_linesize + x_end] != buf[y*linesize + x_end]) {
                    same_column = 0;
                    break;
                }
            }
            if (!same_column)
                break;
            x_end--;
        }
        *width = x_end + 1 - *x_start;

        av_log(avctx, AV_LOG_DEBUG,"%dx%d image at pos (%d;%d) [area:%dx%d]\n",
               *width, *height, *x_start, *y_start, avctx->width, avctx->height);
    }
}
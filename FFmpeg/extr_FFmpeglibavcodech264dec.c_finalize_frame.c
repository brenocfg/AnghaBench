#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_16__ {int* linesize; int height; int /*<<< orphan*/  width; int /*<<< orphan*/  format; int /*<<< orphan*/ ** data; } ;
struct TYPE_15__ {int /*<<< orphan*/  mb_stride; int /*<<< orphan*/  mb_height; int /*<<< orphan*/  mb_width; TYPE_10__* avctx; } ;
struct TYPE_14__ {scalar_t__* field_poc; int /*<<< orphan*/  motion_val; int /*<<< orphan*/  qscale_table; int /*<<< orphan*/  mb_type; TYPE_3__* f; scalar_t__ recovered; } ;
struct TYPE_13__ {int flags; int flags2; int /*<<< orphan*/  hwaccel; } ;
typedef  TYPE_1__ H264Picture ;
typedef  TYPE_2__ H264Context ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */
 int AV_CODEC_FLAG2_SHOW_ALL ; 
 int AV_CODEC_FLAG_OUTPUT_CORRUPT ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 scalar_t__ CONFIG_MPEGVIDEO ; 
 scalar_t__ INT_MAX ; 
 int /*<<< orphan*/  av_image_copy (int /*<<< orphan*/ **,int*,int /*<<< orphan*/  const**,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_log (TYPE_10__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ff_print_debug_info2 (TYPE_10__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int output_frame (TYPE_2__*,TYPE_3__*,TYPE_1__*) ; 

__attribute__((used)) static int finalize_frame(H264Context *h, AVFrame *dst, H264Picture *out, int *got_frame)
{
    int ret;

    if (((h->avctx->flags & AV_CODEC_FLAG_OUTPUT_CORRUPT) ||
         (h->avctx->flags2 & AV_CODEC_FLAG2_SHOW_ALL) ||
         out->recovered)) {

        if (!h->avctx->hwaccel &&
            (out->field_poc[0] == INT_MAX ||
             out->field_poc[1] == INT_MAX)
           ) {
            int p;
            AVFrame *f = out->f;
            int field = out->field_poc[0] == INT_MAX;
            uint8_t *dst_data[4];
            int linesizes[4];
            const uint8_t *src_data[4];

            av_log(h->avctx, AV_LOG_DEBUG, "Duplicating field %d to fill missing\n", field);

            for (p = 0; p<4; p++) {
                dst_data[p] = f->data[p] + (field^1)*f->linesize[p];
                src_data[p] = f->data[p] +  field   *f->linesize[p];
                linesizes[p] = 2*f->linesize[p];
            }

            av_image_copy(dst_data, linesizes, src_data, linesizes,
                          f->format, f->width, f->height>>1);
        }

        ret = output_frame(h, dst, out);
        if (ret < 0)
            return ret;

        *got_frame = 1;

        if (CONFIG_MPEGVIDEO) {
            ff_print_debug_info2(h->avctx, dst, NULL,
                                 out->mb_type,
                                 out->qscale_table,
                                 out->motion_val,
                                 NULL,
                                 h->mb_width, h->mb_height, h->mb_stride, 1);
        }
    }

    return 0;
}
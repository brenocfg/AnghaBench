#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_9__ {int quarter_sample; int mb_num; int mb_width; int mb_height; int mb_stride; int b8_stride; int* mb_index2xy; int* error_status_table; int** dc_val; int /*<<< orphan*/  er_temp_buffer; TYPE_2__* opaque; int /*<<< orphan*/  decode_mb; int /*<<< orphan*/  avctx; } ;
struct TYPE_8__ {int mb_height; int mb_stride; int mb_width; int mb_num; int /*<<< orphan*/  avctx; TYPE_1__* slice_ctx; } ;
struct TYPE_7__ {int* dc_val_base; int /*<<< orphan*/ ** ref_cache; TYPE_3__ er; } ;
typedef  TYPE_1__ H264SliceContext ;
typedef  TYPE_2__ H264Context ;
typedef  TYPE_3__ ERContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ CONFIG_ERROR_RESILIENCE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FF_ALLOCZ_OR_GOTO (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FF_ALLOC_OR_GOTO (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PART_NOT_AVAILABLE ; 
 int /*<<< orphan*/  fail ; 
 int /*<<< orphan*/  h264_er_decode_mb ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int* scan8 ; 

int ff_h264_slice_context_init(H264Context *h, H264SliceContext *sl)
{
    ERContext *er = &sl->er;
    int mb_array_size = h->mb_height * h->mb_stride;
    int y_size  = (2 * h->mb_width + 1) * (2 * h->mb_height + 1);
    int c_size  = h->mb_stride * (h->mb_height + 1);
    int yc_size = y_size + 2   * c_size;
    int x, y, i;

    sl->ref_cache[0][scan8[5]  + 1] =
    sl->ref_cache[0][scan8[7]  + 1] =
    sl->ref_cache[0][scan8[13] + 1] =
    sl->ref_cache[1][scan8[5]  + 1] =
    sl->ref_cache[1][scan8[7]  + 1] =
    sl->ref_cache[1][scan8[13] + 1] = PART_NOT_AVAILABLE;

    if (sl != h->slice_ctx) {
        memset(er, 0, sizeof(*er));
    } else
    if (CONFIG_ERROR_RESILIENCE) {

        /* init ER */
        er->avctx          = h->avctx;
        er->decode_mb      = h264_er_decode_mb;
        er->opaque         = h;
        er->quarter_sample = 1;

        er->mb_num      = h->mb_num;
        er->mb_width    = h->mb_width;
        er->mb_height   = h->mb_height;
        er->mb_stride   = h->mb_stride;
        er->b8_stride   = h->mb_width * 2 + 1;

        // error resilience code looks cleaner with this
        FF_ALLOCZ_OR_GOTO(h->avctx, er->mb_index2xy,
                          (h->mb_num + 1) * sizeof(int), fail);

        for (y = 0; y < h->mb_height; y++)
            for (x = 0; x < h->mb_width; x++)
                er->mb_index2xy[x + y * h->mb_width] = x + y * h->mb_stride;

        er->mb_index2xy[h->mb_height * h->mb_width] = (h->mb_height - 1) *
                                                      h->mb_stride + h->mb_width;

        FF_ALLOCZ_OR_GOTO(h->avctx, er->error_status_table,
                          mb_array_size * sizeof(uint8_t), fail);

        FF_ALLOC_OR_GOTO(h->avctx, er->er_temp_buffer,
                         h->mb_height * h->mb_stride * (4*sizeof(int) + 1), fail);

        FF_ALLOCZ_OR_GOTO(h->avctx, sl->dc_val_base,
                          yc_size * sizeof(int16_t), fail);
        er->dc_val[0] = sl->dc_val_base + h->mb_width * 2 + 2;
        er->dc_val[1] = sl->dc_val_base + y_size + h->mb_stride + 1;
        er->dc_val[2] = er->dc_val[1] + c_size;
        for (i = 0; i < yc_size; i++)
            sl->dc_val_base[i] = 1024;
    }

    return 0;

fail:
    return AVERROR(ENOMEM); // ff_h264_free_tables will clean up for us
}
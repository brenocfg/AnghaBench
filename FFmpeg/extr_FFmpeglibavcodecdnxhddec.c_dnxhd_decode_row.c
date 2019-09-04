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
typedef  scalar_t__ uint32_t ;
struct TYPE_9__ {TYPE_2__* priv_data; } ;
struct TYPE_8__ {int bit_depth; int mb_width; scalar_t__ buf_size; scalar_t__ buf; TYPE_1__* rows; scalar_t__* mb_scan_index; } ;
struct TYPE_7__ {int* last_dc; int /*<<< orphan*/  errors; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ RowContext ;
typedef  TYPE_2__ DNXHDContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int dnxhd_decode_macroblock (TYPE_2__ const*,TYPE_1__*,void*,int,int) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int dnxhd_decode_row(AVCodecContext *avctx, void *data,
                            int rownb, int threadnb)
{
    const DNXHDContext *ctx = avctx->priv_data;
    uint32_t offset = ctx->mb_scan_index[rownb];
    RowContext *row = ctx->rows + threadnb;
    int x, ret;

    row->last_dc[0] =
    row->last_dc[1] =
    row->last_dc[2] = 1 << (ctx->bit_depth + 2); // for levels +2^(bitdepth-1)
    ret = init_get_bits8(&row->gb, ctx->buf + offset, ctx->buf_size - offset);
    if (ret < 0) {
        row->errors++;
        return ret;
    }
    for (x = 0; x < ctx->mb_width; x++) {
        //START_TIMER;
        int ret = dnxhd_decode_macroblock(ctx, row, data, x, rownb);
        if (ret < 0) {
            row->errors++;
            return ret;
        }
        //STOP_TIMER("decode macroblock");
    }

    return 0;
}
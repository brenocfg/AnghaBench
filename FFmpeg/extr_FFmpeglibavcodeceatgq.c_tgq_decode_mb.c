#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  void* int8_t ;
struct TYPE_11__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_10__ {int /*<<< orphan*/  avctx; TYPE_6__ gb; int /*<<< orphan*/ * block; } ;
typedef  TYPE_1__ TgqContext ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  FFMIN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  bytestream2_get_buffer (TYPE_6__*,void**,int) ; 
 void* bytestream2_get_byte (TYPE_6__*) ; 
 int /*<<< orphan*/  bytestream2_get_bytes_left (TYPE_6__*) ; 
 int /*<<< orphan*/  bytestream2_skip (TYPE_6__*,int) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void**,void*,int) ; 
 int /*<<< orphan*/  tgq_decode_block (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tgq_idct_put_mb (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  tgq_idct_put_mb_dconly (TYPE_1__*,int /*<<< orphan*/ *,int,int,void**) ; 

__attribute__((used)) static int tgq_decode_mb(TgqContext *s, AVFrame *frame, int mb_y, int mb_x)
{
    int mode;
    int i;
    int8_t dc[6];

    mode = bytestream2_get_byte(&s->gb);
    if (mode > 12) {
        GetBitContext gb;
        int ret = init_get_bits8(&gb, s->gb.buffer, FFMIN(bytestream2_get_bytes_left(&s->gb), mode));
        if (ret < 0)
            return ret;

        for (i = 0; i < 6; i++)
            tgq_decode_block(s, s->block[i], &gb);
        tgq_idct_put_mb(s, s->block, frame, mb_x, mb_y);
        bytestream2_skip(&s->gb, mode);
    } else {
        if (mode == 3) {
            memset(dc, bytestream2_get_byte(&s->gb), 4);
            dc[4] = bytestream2_get_byte(&s->gb);
            dc[5] = bytestream2_get_byte(&s->gb);
        } else if (mode == 6) {
            bytestream2_get_buffer(&s->gb, dc, 6);
        } else if (mode == 12) {
            for (i = 0; i < 6; i++) {
                dc[i] = bytestream2_get_byte(&s->gb);
                bytestream2_skip(&s->gb, 1);
            }
        } else {
            av_log(s->avctx, AV_LOG_ERROR, "unsupported mb mode %i\n", mode);
            return -1;
        }
        tgq_idct_put_mb_dconly(s, frame, mb_x, mb_y, dc);
    }
    return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_12__ {int /*<<< orphan*/  (* bswap_buf ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ;} ;
struct TYPE_13__ {int mb_y; int mb_x; int /*<<< orphan*/  block; scalar_t__* last_dc; int /*<<< orphan*/  bitstream_buf; int /*<<< orphan*/  gb; TYPE_1__ bsdsp; int /*<<< orphan*/  bitstream_buf_size; TYPE_4__* avctx; } ;
typedef  TYPE_2__ TqiContext ;
struct TYPE_15__ {TYPE_2__* priv_data; } ;
struct TYPE_14__ {int size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_3__ AVPacket ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AV_RL16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_fast_padded_malloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int ff_get_buffer (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ff_set_dimensions (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  tqi_calculate_qtable (TYPE_2__*,int /*<<< orphan*/  const) ; 
 scalar_t__ tqi_decode_mb (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tqi_idct_put (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tqi_decode_frame(AVCodecContext *avctx,
                            void *data, int *got_frame,
                            AVPacket *avpkt)
{
    const uint8_t *buf = avpkt->data;
    int buf_size = avpkt->size;
    const uint8_t *buf_end = buf+buf_size;
    TqiContext *t = avctx->priv_data;
    AVFrame *frame = data;
    int ret, w, h;

    if (buf_size < 12)
        return AVERROR_INVALIDDATA;

    t->avctx = avctx;

    w = AV_RL16(&buf[0]);
    h = AV_RL16(&buf[2]);
    tqi_calculate_qtable(t, buf[4]);
    buf += 8;

    ret = ff_set_dimensions(avctx, w, h);
    if (ret < 0)
        return ret;

    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;

    av_fast_padded_malloc(&t->bitstream_buf, &t->bitstream_buf_size,
                          buf_end - buf);
    if (!t->bitstream_buf)
        return AVERROR(ENOMEM);
    t->bsdsp.bswap_buf(t->bitstream_buf, (const uint32_t *) buf,
                       (buf_end - buf) / 4);
    init_get_bits(&t->gb, t->bitstream_buf, 8 * (buf_end - buf));

    t->last_dc[0] =
    t->last_dc[1] =
    t->last_dc[2] = 0;
    for (t->mb_y = 0; t->mb_y < (h + 15) / 16; t->mb_y++) {
        for (t->mb_x = 0; t->mb_x < (w + 15) / 16; t->mb_x++) {
            if (tqi_decode_mb(t, t->block) < 0)
                goto end;
            tqi_idct_put(avctx, frame, t->block);
        }
    }
    end:

    *got_frame = 1;
    return buf_size;
}
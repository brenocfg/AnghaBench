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
struct TYPE_6__ {TYPE_1__* priv_data; } ;
struct TYPE_5__ {scalar_t__ ts_framing; int /*<<< orphan*/  pc; } ;
typedef  int /*<<< orphan*/  ParseContext ;
typedef  TYPE_1__ OpusParseContext ;
typedef  TYPE_2__ AVCodecParserContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 scalar_t__ ff_combine_frame (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const**,int*) ; 
 int opus_find_frame_end (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int*) ; 

__attribute__((used)) static int opus_parse(AVCodecParserContext *ctx, AVCodecContext *avctx,
                       const uint8_t **poutbuf, int *poutbuf_size,
                       const uint8_t *buf, int buf_size)
{
    OpusParseContext *s = ctx->priv_data;
    ParseContext *pc    = &s->pc;
    int next, header_len;

    next = opus_find_frame_end(ctx, avctx, buf, buf_size, &header_len);

    if (s->ts_framing && next != AVERROR_INVALIDDATA &&
        ff_combine_frame(pc, next, &buf, &buf_size) < 0) {
        *poutbuf      = NULL;
        *poutbuf_size = 0;
        return buf_size;
    }

    if (next == AVERROR_INVALIDDATA){
        *poutbuf      = NULL;
        *poutbuf_size = 0;
        return buf_size;
    }

    *poutbuf      = buf + header_len;
    *poutbuf_size = buf_size - header_len;
    return next;
}
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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {int bit_rate; scalar_t__ codec_id; int channels; int /*<<< orphan*/  frame_size; } ;
struct TYPE_7__ {int /*<<< orphan*/  duration; TYPE_1__* priv_data; } ;
struct TYPE_6__ {int block_size; int remaining; int /*<<< orphan*/  duration; int /*<<< orphan*/  pc; } ;
typedef  int /*<<< orphan*/  ParseContext ;
typedef  TYPE_1__ G729ParseContext ;
typedef  TYPE_2__ AVCodecParserContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_ACELP_KELVIN ; 
 int END_NOT_FOUND ; 
 int G729D_6K4_BLOCK_SIZE ; 
 int G729_8K_BLOCK_SIZE ; 
 scalar_t__ ff_combine_frame (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const**,int*) ; 

__attribute__((used)) static int g729_parse(AVCodecParserContext *s1, AVCodecContext *avctx,
                     const uint8_t **poutbuf, int *poutbuf_size,
                     const uint8_t *buf, int buf_size)
{
    G729ParseContext *s = s1->priv_data;
    ParseContext *pc = &s->pc;
    int next;

    if (!s->block_size) {
        /* FIXME: replace this heuristic block_size with more precise estimate */
        s->block_size = (avctx->bit_rate < 8000) ? G729D_6K4_BLOCK_SIZE : G729_8K_BLOCK_SIZE;
        if (avctx->codec_id == AV_CODEC_ID_ACELP_KELVIN)
            s->block_size++;
        s->block_size *= avctx->channels;
        s->duration   = avctx->frame_size;
    }

    if (!s->block_size) {
        *poutbuf      = buf;
        *poutbuf_size = buf_size;
        return buf_size;
    }

    if (!s->remaining)
        s->remaining = s->block_size;
    if (s->remaining <= buf_size) {
        next = s->remaining;
        s->remaining = 0;
    } else {
        next = END_NOT_FOUND;
        s->remaining -= buf_size;
    }

    if (ff_combine_frame(pc, next, &buf, &buf_size) < 0 || !buf_size) {
        *poutbuf      = NULL;
        *poutbuf_size = 0;
        return buf_size;
    }

    s1->duration = s->duration;

    *poutbuf      = buf;
    *poutbuf_size = buf_size;
    return next;
}
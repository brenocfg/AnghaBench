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
struct TYPE_8__ {int codec_id; int block_align; } ;
struct TYPE_7__ {int duration; TYPE_1__* priv_data; } ;
struct TYPE_6__ {int block_size; int duration; int remaining; int /*<<< orphan*/  pc; } ;
typedef  int /*<<< orphan*/  ParseContext ;
typedef  TYPE_1__ GSMParseContext ;
typedef  TYPE_2__ AVCodecParserContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
#define  AV_CODEC_ID_GSM 129 
#define  AV_CODEC_ID_GSM_MS 128 
 int END_NOT_FOUND ; 
 int GSM_BLOCK_SIZE ; 
 int GSM_FRAME_SIZE ; 
 int GSM_MS_BLOCK_SIZE ; 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 scalar_t__ ff_combine_frame (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const**,int*) ; 

__attribute__((used)) static int gsm_parse(AVCodecParserContext *s1, AVCodecContext *avctx,
                     const uint8_t **poutbuf, int *poutbuf_size,
                     const uint8_t *buf, int buf_size)
{
    GSMParseContext *s = s1->priv_data;
    ParseContext *pc = &s->pc;
    int next;

    if (!s->block_size) {
        switch (avctx->codec_id) {
        case AV_CODEC_ID_GSM:
            s->block_size = GSM_BLOCK_SIZE;
            s->duration   = GSM_FRAME_SIZE;
            break;
        case AV_CODEC_ID_GSM_MS:
            s->block_size = avctx->block_align ? avctx->block_align
                                               : GSM_MS_BLOCK_SIZE;
            s->duration   = GSM_FRAME_SIZE * 2;
            break;
        default:
            av_assert0(0);
        }
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
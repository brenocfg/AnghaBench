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
typedef  int uint8_t ;
typedef  int uint64_t ;
struct TYPE_6__ {int state64; } ;
struct TYPE_8__ {int header_size; int block_size; int remaining; TYPE_1__ pc; } ;
struct TYPE_7__ {int /*<<< orphan*/  duration; TYPE_3__* priv_data; } ;
typedef  TYPE_1__ ParseContext ;
typedef  TYPE_2__ AVCodecParserContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;
typedef  TYPE_3__ ADXParseContext ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_SAMPLES ; 
 int BLOCK_SIZE ; 
 int END_NOT_FOUND ; 
 scalar_t__ ff_combine_frame (TYPE_1__*,int,int const**,int*) ; 

__attribute__((used)) static int adx_parse(AVCodecParserContext *s1,
                           AVCodecContext *avctx,
                           const uint8_t **poutbuf, int *poutbuf_size,
                           const uint8_t *buf, int buf_size)
{
    ADXParseContext *s = s1->priv_data;
    ParseContext *pc = &s->pc;
    int next = END_NOT_FOUND;
    int i;
    uint64_t state = pc->state64;

    if (!s->header_size) {
        for (i = 0; i < buf_size; i++) {
            state = (state << 8) | buf[i];
            /* check for fixed fields in ADX header for possible match */
            if ((state & 0xFFFF0000FFFFFF00) == 0x8000000003120400ULL) {
                int channels    = state & 0xFF;
                int header_size = ((state >> 32) & 0xFFFF) + 4;
                if (channels > 0 && header_size >= 8) {
                    s->header_size = header_size;
                    s->block_size  = BLOCK_SIZE * channels;
                    s->remaining   = i - 7 + s->header_size + s->block_size;
                    break;
                }
            }
        }
        pc->state64 = state;
    }

    if (s->header_size) {
        if (!s->remaining)
            s->remaining = s->block_size;
        if (s->remaining <= buf_size) {
            next = s->remaining;
            s->remaining = 0;
        } else
            s->remaining -= buf_size;
    }

    if (ff_combine_frame(pc, next, &buf, &buf_size) < 0 || !buf_size) {
        *poutbuf      = NULL;
        *poutbuf_size = 0;
        return buf_size;
    }

    s1->duration = BLOCK_SAMPLES;

    *poutbuf = buf;
    *poutbuf_size = buf_size;
    return next;
}
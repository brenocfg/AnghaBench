#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_11__ {int flags; int key_frame; scalar_t__ duration; TYPE_2__* priv_data; } ;
struct TYPE_10__ {int index; int* buffer; int frame_start_found; int /*<<< orphan*/  overread; } ;
struct TYPE_8__ {int flags; scalar_t__ frame_samples; scalar_t__ last_frame_samples; } ;
struct TYPE_9__ {int index; TYPE_1__ ti; TYPE_3__ pc; } ;
typedef  TYPE_1__ TAKStreamInfo ;
typedef  TYPE_2__ TAKParseContext ;
typedef  TYPE_3__ ParseContext ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_4__ AVCodecParserContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int END_NOT_FOUND ; 
 int /*<<< orphan*/  FFMAX (int /*<<< orphan*/ ,int) ; 
 int FFMIN (int,int) ; 
 int PARSER_FLAG_COMPLETE_FRAMES ; 
 int TAK_FRAME_FLAG_HAS_INFO ; 
 int TAK_MAX_FRAME_HEADER_BYTES ; 
 scalar_t__ ff_combine_frame (TYPE_3__*,int,int const**,int*) ; 
 int /*<<< orphan*/  ff_tak_check_crc (int const*,int) ; 
 int /*<<< orphan*/  ff_tak_decode_frame_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,int const*,int) ; 

__attribute__((used)) static int tak_parse(AVCodecParserContext *s, AVCodecContext *avctx,
                     const uint8_t **poutbuf, int *poutbuf_size,
                     const uint8_t *buf, int buf_size)
{
    TAKParseContext *t = s->priv_data;
    ParseContext *pc   = &t->pc;
    int next           = END_NOT_FOUND;
    GetBitContext gb;
    int consumed = 0;
    int needed   = buf_size ? TAK_MAX_FRAME_HEADER_BYTES : 8;
    int ret;

    *poutbuf      = buf;
    *poutbuf_size = buf_size;

    if (s->flags & PARSER_FLAG_COMPLETE_FRAMES) {
        TAKStreamInfo ti;
        if ((ret = init_get_bits8(&gb, buf, buf_size)) < 0)
            return buf_size;
        if (!ff_tak_decode_frame_header(avctx, &gb, &ti, 127))
            s->duration = t->ti.last_frame_samples ? t->ti.last_frame_samples
                                                   : t->ti.frame_samples;
        return buf_size;
    }

    while (buf_size || t->index + needed <= pc->index) {
        if (buf_size && t->index + TAK_MAX_FRAME_HEADER_BYTES > pc->index) {
            int tmp_buf_size       = FFMIN(TAK_MAX_FRAME_HEADER_BYTES,
                                           buf_size);
            const uint8_t *tmp_buf = buf;

            if (ff_combine_frame(pc, END_NOT_FOUND, &tmp_buf, &tmp_buf_size) != -1)
                goto fail;
            consumed += tmp_buf_size;
            buf      += tmp_buf_size;
            buf_size -= tmp_buf_size;
        }

        for (; t->index + needed <= pc->index; t->index++) {
            if (pc->buffer[ t->index     ] == 0xFF &&
                pc->buffer[ t->index + 1 ] == 0xA0) {
                TAKStreamInfo ti;

                if ((ret = init_get_bits8(&gb, pc->buffer + t->index,
                                          pc->index - t->index)) < 0)
                    goto fail;
                if (!ff_tak_decode_frame_header(avctx, &gb,
                        pc->frame_start_found ? &ti : &t->ti, 127) &&
                    !ff_tak_check_crc(pc->buffer + t->index,
                                      get_bits_count(&gb) / 8)) {
                    if (!pc->frame_start_found) {
                        pc->frame_start_found = 1;
                        s->duration           = t->ti.last_frame_samples ?
                                                t->ti.last_frame_samples :
                                                t->ti.frame_samples;
                        s->key_frame          = !!(t->ti.flags & TAK_FRAME_FLAG_HAS_INFO);
                    } else {
                        pc->frame_start_found = 0;
                        next                  = t->index - pc->index;
                        t->index              = 0;
                        goto found;
                    }
                }
            }
        }
    }
found:

    if (consumed && !buf_size && next == END_NOT_FOUND ||
        ff_combine_frame(pc, next, &buf, &buf_size) < 0) {
        goto fail;
    }

    if (next != END_NOT_FOUND) {
        next        += consumed;
        pc->overread = FFMAX(0, -next);
    }

    *poutbuf      = buf;
    *poutbuf_size = buf_size;
    return next;

fail:
    *poutbuf      = NULL;
    *poutbuf_size = 0;
    return buf_size + consumed;
}
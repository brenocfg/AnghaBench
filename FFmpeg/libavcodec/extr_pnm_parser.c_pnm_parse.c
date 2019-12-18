#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const uint8_t ;
struct TYPE_15__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pix_fmt; } ;
struct TYPE_14__ {TYPE_2__* priv_data; } ;
struct TYPE_13__ {scalar_t__ bytestream_start; scalar_t__ bytestream; scalar_t__ bytestream_end; int type; } ;
struct TYPE_11__ {scalar_t__ overread; scalar_t__ buffer; scalar_t__ index; scalar_t__ overread_index; } ;
struct TYPE_12__ {int remaining_bytes; int ascii_scan; TYPE_1__ pc; } ;
typedef  TYPE_1__ ParseContext ;
typedef  TYPE_2__ PNMParseContext ;
typedef  TYPE_3__ PNMContext ;
typedef  TYPE_4__ AVCodecParserContext ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int END_NOT_FOUND ; 
 unsigned int FFMAX (int,int) ; 
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int av_image_get_buffer_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ff_combine_frame (TYPE_1__*,int,int /*<<< orphan*/  const**,int*) ; 
 scalar_t__ ff_pnm_decode_header (TYPE_5__*,TYPE_3__*) ; 
 int /*<<< orphan*/  const* memchr (int /*<<< orphan*/  const*,char,int) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int pnm_parse(AVCodecParserContext *s, AVCodecContext *avctx,
                     const uint8_t **poutbuf, int *poutbuf_size,
                     const uint8_t *buf, int buf_size)
{
    PNMParseContext *pnmpc = s->priv_data;
    ParseContext *pc = &pnmpc->pc;
    PNMContext pnmctx;
    int next = END_NOT_FOUND;
    int skip = 0;

    if (pc->overread > 0) {
        memmove(pc->buffer + pc->index, pc->buffer + pc->overread_index, pc->overread);
        pc->index          += pc->overread;
        pc->overread_index += pc->overread;
        pc->overread = 0;
    }

    if (pnmpc->remaining_bytes) {
        int inc = FFMIN(pnmpc->remaining_bytes, buf_size);
        skip += inc;
        pnmpc->remaining_bytes -= inc;

        if (!pnmpc->remaining_bytes)
            next = skip;
        goto end;
    }

retry:
    if (pc->index) {
        pnmctx.bytestream_start =
        pnmctx.bytestream       = pc->buffer;
        pnmctx.bytestream_end   = pc->buffer + pc->index;
    } else {
        pnmctx.bytestream_start =
        pnmctx.bytestream       = (uint8_t *) buf + skip; /* casts avoid warnings */
        pnmctx.bytestream_end   = (uint8_t *) buf + buf_size - skip;
    }
    if (ff_pnm_decode_header(avctx, &pnmctx) < 0) {
        if (pnmctx.bytestream < pnmctx.bytestream_end) {
            if (pc->index) {
                pc->index = 0;
                pnmpc->ascii_scan = 0;
            } else {
                unsigned step = FFMAX(1, pnmctx.bytestream - pnmctx.bytestream_start);

                skip += step;
            }
            goto retry;
        }
    } else if (pnmctx.type < 4) {
              uint8_t *bs  = pnmctx.bytestream;
        const uint8_t *end = pnmctx.bytestream_end;
        uint8_t *sync      = bs;

        if (pc->index) {
            av_assert0(pnmpc->ascii_scan <= end - bs);
            bs += pnmpc->ascii_scan;
        }

        while (bs < end) {
            int c;
            sync = bs;
            c = *bs++;
            if (c == '#')  {
                uint8_t *match = memchr(bs, '\n', end-bs);
                if (match)
                    bs = match + 1;
                else
                    break;
            } else if (c == 'P') {
                next = bs - pnmctx.bytestream_start + skip - 1;
                pnmpc->ascii_scan = 0;
                break;
            }
        }
        if (next == END_NOT_FOUND)
            pnmpc->ascii_scan = sync - pnmctx.bytestream + skip;
    } else {
        next = pnmctx.bytestream - pnmctx.bytestream_start + skip
               + av_image_get_buffer_size(avctx->pix_fmt, avctx->width, avctx->height, 1);
    }
    if (next != END_NOT_FOUND && pnmctx.bytestream_start != buf + skip)
        next -= pc->index;
    if (next > buf_size) {
        pnmpc->remaining_bytes = next - buf_size;
        next = END_NOT_FOUND;
    }
end:
    if (ff_combine_frame(pc, next, &buf, &buf_size) < 0) {
        *poutbuf      = NULL;
        *poutbuf_size = 0;
        return buf_size;
    }
    *poutbuf      = buf;
    *poutbuf_size = buf_size;
    return next;
}
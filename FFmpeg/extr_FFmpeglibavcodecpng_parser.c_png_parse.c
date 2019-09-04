#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint64_t ;
struct TYPE_7__ {int frame_start_found; int state64; int state; } ;
struct TYPE_6__ {int /*<<< orphan*/  pict_type; TYPE_1__* priv_data; } ;
struct TYPE_5__ {int remaining_size; int chunk_pos; int chunk_length; TYPE_4__ pc; } ;
typedef  TYPE_1__ PNGParseContext ;
typedef  TYPE_2__ AVCodecParserContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_PICTURE_TYPE_NONE ; 
 int END_NOT_FOUND ; 
 int FFMIN (int,int) ; 
 int MKBETAG (char,char,char,char) ; 
 int MNGSIG ; 
 int PNGSIG ; 
 scalar_t__ ff_combine_frame (TYPE_4__*,int,int const**,int*) ; 

__attribute__((used)) static int png_parse(AVCodecParserContext *s, AVCodecContext *avctx,
                     const uint8_t **poutbuf, int *poutbuf_size,
                     const uint8_t *buf, int buf_size)
{
    PNGParseContext *ppc = s->priv_data;
    int next = END_NOT_FOUND;
    int i = 0;

    s->pict_type = AV_PICTURE_TYPE_NONE;

    *poutbuf_size = 0;

    if (!ppc->pc.frame_start_found) {
        uint64_t state64 = ppc->pc.state64;
        for (; i < buf_size; i++) {
            state64 = (state64 << 8) | buf[i];
            if (state64 == PNGSIG || state64 == MNGSIG) {
                i++;
                ppc->pc.frame_start_found = 1;
                break;
            }
        }
        ppc->pc.state64 = state64;
    } else if (ppc->remaining_size) {
        i = FFMIN(ppc->remaining_size, buf_size);
        ppc->remaining_size -= i;
        if (ppc->remaining_size)
            goto flush;
        if (ppc->chunk_pos == -1) {
            next = i;
            goto flush;
        }
    }

    for (; ppc->pc.frame_start_found && i < buf_size; i++) {
        ppc->pc.state = (ppc->pc.state << 8) | buf[i];
        if (ppc->chunk_pos == 3) {
            ppc->chunk_length = ppc->pc.state;
            if (ppc->chunk_length > 0x7fffffff) {
                ppc->chunk_pos = ppc->pc.frame_start_found = 0;
                goto flush;
            }
            ppc->chunk_length += 4;
        } else if (ppc->chunk_pos == 7) {
            if (ppc->chunk_length >= buf_size - i)
                ppc->remaining_size = ppc->chunk_length - buf_size + i + 1;
            if (ppc->pc.state == MKBETAG('I', 'E', 'N', 'D')) {
                if (ppc->remaining_size)
                    ppc->chunk_pos = -1;
                else
                    next = ppc->chunk_length + i + 1;
                break;
            } else {
                ppc->chunk_pos = 0;
                if (ppc->remaining_size)
                    break;
                else
                    i += ppc->chunk_length;
                continue;
            }
        }
        ppc->chunk_pos++;
    }

flush:
    if (ff_combine_frame(&ppc->pc, next, &buf, &buf_size) < 0)
        return buf_size;

    ppc->chunk_pos = ppc->pc.frame_start_found = 0;

    *poutbuf      = buf;
    *poutbuf_size = buf_size;
    return next;
}
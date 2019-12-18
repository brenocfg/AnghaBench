#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_7__ {int state; int frame_start_found; } ;
struct TYPE_6__ {int /*<<< orphan*/  pict_type; TYPE_1__* priv_data; } ;
struct TYPE_5__ {int is_be; int index; int remaining_size; int fsize; TYPE_3__ pc; } ;
typedef  TYPE_1__ DPXParseContext ;
typedef  TYPE_2__ AVCodecParserContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int END_NOT_FOUND ; 
 int FFMIN (int,int) ; 
 int MKBETAG (char,char,char,char) ; 
 int MKTAG (char,char,char,char) ; 
 int av_bswap32 (int) ; 
 scalar_t__ ff_combine_frame (TYPE_3__*,int,int const**,int*) ; 

__attribute__((used)) static int dpx_parse(AVCodecParserContext *s, AVCodecContext *avctx,
                     const uint8_t **poutbuf, int *poutbuf_size,
                     const uint8_t *buf, int buf_size)
{
    DPXParseContext *d = s->priv_data;
    uint32_t state = d->pc.state;
    int next = END_NOT_FOUND;
    int i = 0;

    s->pict_type = AV_PICTURE_TYPE_I;

    *poutbuf_size = 0;
    if (buf_size == 0)
        next = 0;

    if (!d->pc.frame_start_found) {
        for (; i < buf_size; i++) {
            state = (state << 8) | buf[i];
            if (state == MKBETAG('S','D','P','X') ||
                state == MKTAG('S','D','P','X')) {
                d->pc.frame_start_found = 1;
                d->is_be = state == MKBETAG('S','D','P','X');
                d->index = 0;
                break;
            }
        }
        d->pc.state = state;
    } else {
        if (d->remaining_size) {
            i = FFMIN(d->remaining_size, buf_size);
            d->remaining_size -= i;
            if (d->remaining_size)
                goto flush;
        }
    }

    for (; d->pc.frame_start_found && i < buf_size; i++) {
        d->pc.state = (d->pc.state << 8) | buf[i];
        d->index++;
        if (d->index == 17) {
            d->fsize = d->is_be ? d->pc.state : av_bswap32(d->pc.state);
            if (d->fsize <= 1664) {
                d->pc.frame_start_found = 0;
                goto flush;
            }
            if (d->fsize > buf_size - i + 19)
                d->remaining_size = d->fsize - buf_size + i - 19;
            else
                i += d->fsize - 19;

            break;
        } else if (d->index > 17) {
            if (d->pc.state == MKBETAG('S','D','P','X') ||
                d->pc.state == MKTAG('S','D','P','X')) {
                next = i - 3;
                break;
            }
        }
    }

flush:
    if (ff_combine_frame(&d->pc, next, &buf, &buf_size) < 0)
        return buf_size;

    d->pc.frame_start_found = 0;

    *poutbuf      = buf;
    *poutbuf_size = buf_size;
    return next;
}
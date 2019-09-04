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
typedef  int uint64_t ;
struct TYPE_7__ {int state64; int frame_start_found; int index; } ;
struct TYPE_6__ {TYPE_1__* priv_data; } ;
struct TYPE_5__ {int fsize; int remaining_size; TYPE_3__ pc; } ;
typedef  TYPE_1__ BMPParseContext ;
typedef  TYPE_2__ AVCodecParserContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int END_NOT_FOUND ; 
 int FFMAX (int,int /*<<< orphan*/ ) ; 
 int FFMIN (int,int) ; 
 void* av_bswap32 (int) ; 
 scalar_t__ ff_combine_frame (TYPE_3__*,int,int const**,int*) ; 

__attribute__((used)) static int bmp_parse(AVCodecParserContext *s, AVCodecContext *avctx,
                     const uint8_t **poutbuf, int *poutbuf_size,
                     const uint8_t *buf, int buf_size)
{
    BMPParseContext *bpc = s->priv_data;
    uint64_t state = bpc->pc.state64;
    int next = END_NOT_FOUND;
    int i = 0;

    *poutbuf_size = 0;

restart:
    if (bpc->pc.frame_start_found <= 2+4+4) {
        for (; i < buf_size; i++) {
            state = (state << 8) | buf[i];
            if (bpc->pc.frame_start_found == 0) {
                if ((state >> 48) == (('B' << 8) | 'M')) {
                    bpc->fsize = av_bswap32(state >> 16);
                    if (bpc->fsize > 17)
                        bpc->pc.frame_start_found = 1;
                }
            } else if (bpc->pc.frame_start_found == 2+4+4) {
//                 unsigned hsize = av_bswap32(state>>32);
                unsigned ihsize = av_bswap32(state);
                if (ihsize < 12 || ihsize > 200) {
                    bpc->pc.frame_start_found = 0;
                    continue;
                }
                bpc->pc.frame_start_found++;
                bpc->remaining_size = bpc->fsize + i - 17;

                if (bpc->pc.index + i > 17) {
                    next = i - 17;
                    state = 0;
                    break;
                } else {
                    bpc->pc.state64 = 0;
                    goto restart;
                }
            } else if (bpc->pc.frame_start_found)
                bpc->pc.frame_start_found++;
        }
        bpc->pc.state64 = state;
    } else {
        if (bpc->remaining_size) {
            i = FFMIN(bpc->remaining_size, buf_size);
            bpc->remaining_size -= i;
            if (bpc->remaining_size)
                goto flush;

            bpc->pc.frame_start_found = 0;
            goto restart;
        }
    }

flush:
    if (ff_combine_frame(&bpc->pc, next, &buf, &buf_size) < 0)
        return buf_size;

    if (next != END_NOT_FOUND && next < 0)
        bpc->pc.frame_start_found = FFMAX(bpc->pc.frame_start_found - i - 1, 0);
    else
        bpc->pc.frame_start_found = 0;

    *poutbuf      = buf;
    *poutbuf_size = buf_size;
    return next;
}
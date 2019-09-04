#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  intbuf ;
struct TYPE_20__ {int* bitmap; } ;
typedef  TYPE_3__ XFaceContext ;
struct TYPE_25__ {int width; scalar_t__ height; TYPE_3__* priv_data; } ;
struct TYPE_24__ {int** data; int /*<<< orphan*/ * linesize; } ;
struct TYPE_23__ {int* data; int /*<<< orphan*/  flags; } ;
struct TYPE_22__ {scalar_t__ nb_words; int /*<<< orphan*/  member_0; } ;
struct TYPE_19__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_18__ {TYPE_2__ member_0; } ;
struct TYPE_21__ {size_t prob_ranges_idx; int /*<<< orphan*/ * prob_ranges; int /*<<< orphan*/  member_1; TYPE_1__ member_0; } ;
typedef  TYPE_4__ ProbRangesQueue ;
typedef  TYPE_5__ BigInt ;
typedef  TYPE_6__ AVPacket ;
typedef  TYPE_7__ AVFrame ;
typedef  TYPE_8__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  EINVAL ; 
 int XFACE_FIRST_PRINT ; 
 scalar_t__ XFACE_HEIGHT ; 
 int XFACE_MAX_DIGITS ; 
 scalar_t__ XFACE_MAX_WORDS ; 
 int XFACE_PIXELS ; 
 int /*<<< orphan*/  XFACE_PRINTS ; 
 int XFACE_WIDTH ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_log (TYPE_8__*,int /*<<< orphan*/ ,char*,int,scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  encode_block (int*,int,int,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int ff_alloc_packet2 (TYPE_8__*,TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_big_div (TYPE_5__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ff_xface_generate_face (int*,int*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  push_integer (TYPE_5__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int xface_encode_frame(AVCodecContext *avctx, AVPacket *pkt,
                              const AVFrame *frame, int *got_packet)
{
    XFaceContext *xface = avctx->priv_data;
    ProbRangesQueue pq = {{{ 0 }}, 0};
    uint8_t bitmap_copy[XFACE_PIXELS];
    BigInt b = {0};
    int i, j, k, ret = 0;
    const uint8_t *buf;
    uint8_t *p;
    char intbuf[XFACE_MAX_DIGITS];

    if (avctx->width || avctx->height) {
        if (avctx->width != XFACE_WIDTH || avctx->height != XFACE_HEIGHT) {
            av_log(avctx, AV_LOG_ERROR,
                   "Size value %dx%d not supported, only accepts a size of %dx%d\n",
                   avctx->width, avctx->height, XFACE_WIDTH, XFACE_HEIGHT);
            return AVERROR(EINVAL);
        }
    }
    avctx->width  = XFACE_WIDTH;
    avctx->height = XFACE_HEIGHT;

    /* convert image from MONOWHITE to 1=black 0=white bitmap */
    buf = frame->data[0];
    i = j = 0;
    do {
        for (k = 0; k < 8; k++)
            xface->bitmap[i++] = (buf[j]>>(7-k))&1;
        if (++j == XFACE_WIDTH/8) {
            buf += frame->linesize[0];
            j = 0;
        }
    } while (i < XFACE_PIXELS);

    /* create a copy of bitmap */
    memcpy(bitmap_copy, xface->bitmap, XFACE_PIXELS);
    ff_xface_generate_face(xface->bitmap, bitmap_copy);

    encode_block(xface->bitmap,                         16, 16, 0, &pq);
    encode_block(xface->bitmap + 16,                    16, 16, 0, &pq);
    encode_block(xface->bitmap + 32,                    16, 16, 0, &pq);
    encode_block(xface->bitmap + XFACE_WIDTH * 16,      16, 16, 0, &pq);
    encode_block(xface->bitmap + XFACE_WIDTH * 16 + 16, 16, 16, 0, &pq);
    encode_block(xface->bitmap + XFACE_WIDTH * 16 + 32, 16, 16, 0, &pq);
    encode_block(xface->bitmap + XFACE_WIDTH * 32,      16, 16, 0, &pq);
    encode_block(xface->bitmap + XFACE_WIDTH * 32 + 16, 16, 16, 0, &pq);
    encode_block(xface->bitmap + XFACE_WIDTH * 32 + 32, 16, 16, 0, &pq);

    while (pq.prob_ranges_idx > 0)
        push_integer(&b, &pq.prob_ranges[--pq.prob_ranges_idx]);

    /* write the inverted big integer in b to intbuf */
    i = 0;
    av_assert0(b.nb_words < XFACE_MAX_WORDS);
    while (b.nb_words) {
        uint8_t r;
        ff_big_div(&b, XFACE_PRINTS, &r);
        av_assert0(i < sizeof(intbuf));
        intbuf[i++] = r + XFACE_FIRST_PRINT;
    }

    if ((ret = ff_alloc_packet2(avctx, pkt, i+2, 0)) < 0)
        return ret;

    /* revert the number, and close the buffer */
    p = pkt->data;
    while (--i >= 0)
        *(p++) = intbuf[i];
    *(p++) = '\n';
    *(p++) = 0;

    pkt->flags |= AV_PKT_FLAG_KEY;
    *got_packet = 1;

    return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int flags2; } ;
struct TYPE_7__ {int buf_end; int buf; } ;
struct TYPE_6__ {int bps; int flags; int** temp; int** len; int** bits; int n; int** temp16; TYPE_2__ pb; int /*<<< orphan*/ ** stats; scalar_t__ context; TYPE_5__* avctx; } ;
typedef  TYPE_1__ HYuvContext ;

/* Variables and functions */
 int AV_CODEC_FLAG2_NO_OUTPUT ; 
 int AV_CODEC_FLAG_PASS1 ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  put_bits (TYPE_2__*,int,int) ; 
 int put_bits_count (TYPE_2__*) ; 

__attribute__((used)) static int encode_plane_bitstream(HYuvContext *s, int width, int plane)
{
    int i, count = width/2;

    if (s->pb.buf_end - s->pb.buf - (put_bits_count(&s->pb) >> 3) < count * s->bps / 2) {
        av_log(s->avctx, AV_LOG_ERROR, "encoded frame too large\n");
        return -1;
    }

#define LOADEND\
            int y0 = s->temp[0][width-1];
#define LOADEND_14\
            int y0 = s->temp16[0][width-1] & mask;
#define LOADEND_16\
            int y0 = s->temp16[0][width-1];
#define STATEND\
            s->stats[plane][y0]++;
#define STATEND_16\
            s->stats[plane][y0>>2]++;
#define WRITEEND\
            put_bits(&s->pb, s->len[plane][y0], s->bits[plane][y0]);
#define WRITEEND_16\
            put_bits(&s->pb, s->len[plane][y0>>2], s->bits[plane][y0>>2]);\
            put_bits(&s->pb, 2, y0&3);

#define LOAD2\
            int y0 = s->temp[0][2 * i];\
            int y1 = s->temp[0][2 * i + 1];
#define LOAD2_14\
            int y0 = s->temp16[0][2 * i] & mask;\
            int y1 = s->temp16[0][2 * i + 1] & mask;
#define LOAD2_16\
            int y0 = s->temp16[0][2 * i];\
            int y1 = s->temp16[0][2 * i + 1];
#define STAT2\
            s->stats[plane][y0]++;\
            s->stats[plane][y1]++;
#define STAT2_16\
            s->stats[plane][y0>>2]++;\
            s->stats[plane][y1>>2]++;
#define WRITE2\
            put_bits(&s->pb, s->len[plane][y0], s->bits[plane][y0]);\
            put_bits(&s->pb, s->len[plane][y1], s->bits[plane][y1]);
#define WRITE2_16\
            put_bits(&s->pb, s->len[plane][y0>>2], s->bits[plane][y0>>2]);\
            put_bits(&s->pb, 2, y0&3);\
            put_bits(&s->pb, s->len[plane][y1>>2], s->bits[plane][y1>>2]);\
            put_bits(&s->pb, 2, y1&3);

    if (s->bps <= 8) {
    if (s->flags & AV_CODEC_FLAG_PASS1) {
        for (i = 0; i < count; i++) {
            LOAD2;
            STAT2;
        }
        if (width&1) {
            LOADEND;
            STATEND;
        }
    }
    if (s->avctx->flags2 & AV_CODEC_FLAG2_NO_OUTPUT)
        return 0;

    if (s->context) {
        for (i = 0; i < count; i++) {
            LOAD2;
            STAT2;
            WRITE2;
        }
        if (width&1) {
            LOADEND;
            STATEND;
            WRITEEND;
        }
    } else {
        for (i = 0; i < count; i++) {
            LOAD2;
            WRITE2;
        }
        if (width&1) {
            LOADEND;
            WRITEEND;
        }
    }
    } else if (s->bps <= 14) {
        int mask = s->n - 1;
        if (s->flags & AV_CODEC_FLAG_PASS1) {
            for (i = 0; i < count; i++) {
                LOAD2_14;
                STAT2;
            }
            if (width&1) {
                LOADEND_14;
                STATEND;
            }
        }
        if (s->avctx->flags2 & AV_CODEC_FLAG2_NO_OUTPUT)
            return 0;

        if (s->context) {
            for (i = 0; i < count; i++) {
                LOAD2_14;
                STAT2;
                WRITE2;
            }
            if (width&1) {
                LOADEND_14;
                STATEND;
                WRITEEND;
            }
        } else {
            for (i = 0; i < count; i++) {
                LOAD2_14;
                WRITE2;
            }
            if (width&1) {
                LOADEND_14;
                WRITEEND;
            }
        }
    } else {
        if (s->flags & AV_CODEC_FLAG_PASS1) {
            for (i = 0; i < count; i++) {
                LOAD2_16;
                STAT2_16;
            }
            if (width&1) {
                LOADEND_16;
                STATEND_16;
            }
        }
        if (s->avctx->flags2 & AV_CODEC_FLAG2_NO_OUTPUT)
            return 0;

        if (s->context) {
            for (i = 0; i < count; i++) {
                LOAD2_16;
                STAT2_16;
                WRITE2_16;
            }
            if (width&1) {
                LOADEND_16;
                STATEND_16;
                WRITEEND_16;
            }
        } else {
            for (i = 0; i < count; i++) {
                LOAD2_16;
                WRITE2_16;
            }
            if (width&1) {
                LOADEND_16;
                WRITEEND_16;
            }
        }
    }
#undef LOAD2
#undef STAT2
#undef WRITE2
    return 0;
}
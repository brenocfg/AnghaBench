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
struct TYPE_6__ {int flags; int** temp; int /*<<< orphan*/ ** bits; int /*<<< orphan*/ ** len; TYPE_2__ pb; int /*<<< orphan*/ ** stats; scalar_t__ context; TYPE_5__* avctx; } ;
typedef  TYPE_1__ HYuvContext ;

/* Variables and functions */
 int A ; 
 int AV_CODEC_FLAG2_NO_OUTPUT ; 
 int AV_CODEC_FLAG_PASS1 ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int B ; 
 int G ; 
 int R ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  put_bits (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int put_bits_count (TYPE_2__*) ; 

__attribute__((used)) static inline int encode_bgra_bitstream(HYuvContext *s, int count, int planes)
{
    int i;

    if (s->pb.buf_end - s->pb.buf - (put_bits_count(&s->pb) >> 3) <
        4 * planes * count) {
        av_log(s->avctx, AV_LOG_ERROR, "encoded frame too large\n");
        return -1;
    }

#define LOAD_GBRA                                                       \
    int g = s->temp[0][planes == 3 ? 3 * i + 1 : 4 * i + G];            \
    int b =(s->temp[0][planes == 3 ? 3 * i + 2 : 4 * i + B] - g) & 0xFF;\
    int r =(s->temp[0][planes == 3 ? 3 * i + 0 : 4 * i + R] - g) & 0xFF;\
    int a = s->temp[0][planes * i + A];

#define STAT_BGRA                                                       \
    s->stats[0][b]++;                                                   \
    s->stats[1][g]++;                                                   \
    s->stats[2][r]++;                                                   \
    if (planes == 4)                                                    \
        s->stats[2][a]++;

#define WRITE_GBRA                                                      \
    put_bits(&s->pb, s->len[1][g], s->bits[1][g]);                      \
    put_bits(&s->pb, s->len[0][b], s->bits[0][b]);                      \
    put_bits(&s->pb, s->len[2][r], s->bits[2][r]);                      \
    if (planes == 4)                                                    \
        put_bits(&s->pb, s->len[2][a], s->bits[2][a]);

    if ((s->flags & AV_CODEC_FLAG_PASS1) &&
        (s->avctx->flags2 & AV_CODEC_FLAG2_NO_OUTPUT)) {
        for (i = 0; i < count; i++) {
            LOAD_GBRA;
            STAT_BGRA;
        }
    } else if (s->context || (s->flags & AV_CODEC_FLAG_PASS1)) {
        for (i = 0; i < count; i++) {
            LOAD_GBRA;
            STAT_BGRA;
            WRITE_GBRA;
        }
    } else {
        for (i = 0; i < count; i++) {
            LOAD_GBRA;
            WRITE_GBRA;
        }
    }
    return 0;
}
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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {int flags2; } ;
struct TYPE_7__ {int buf_end; int buf; } ;
struct TYPE_6__ {int flags; int /*<<< orphan*/ ** bits; int /*<<< orphan*/ ** len; TYPE_2__ pb; int /*<<< orphan*/ ** stats; scalar_t__ context; TYPE_5__* avctx; int /*<<< orphan*/ ** temp; } ;
typedef  TYPE_1__ HYuvContext ;

/* Variables and functions */
 int AV_CODEC_FLAG2_NO_OUTPUT ; 
 int AV_CODEC_FLAG_PASS1 ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  LOAD4 ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  put_bits (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int put_bits_count (TYPE_2__*) ; 
 size_t u0 ; 
 size_t v0 ; 
 size_t y0 ; 
 size_t y1 ; 

__attribute__((used)) static int encode_422_bitstream(HYuvContext *s, int offset, int count)
{
    int i;
    const uint8_t *y = s->temp[0] + offset;
    const uint8_t *u = s->temp[1] + offset / 2;
    const uint8_t *v = s->temp[2] + offset / 2;

    if (s->pb.buf_end - s->pb.buf - (put_bits_count(&s->pb) >> 3) < 2 * 4 * count) {
        av_log(s->avctx, AV_LOG_ERROR, "encoded frame too large\n");
        return -1;
    }

#define LOAD4\
            int y0 = y[2 * i];\
            int y1 = y[2 * i + 1];\
            int u0 = u[i];\
            int v0 = v[i];

    count /= 2;

    if (s->flags & AV_CODEC_FLAG_PASS1) {
        for(i = 0; i < count; i++) {
            LOAD4;
            s->stats[0][y0]++;
            s->stats[1][u0]++;
            s->stats[0][y1]++;
            s->stats[2][v0]++;
        }
    }
    if (s->avctx->flags2 & AV_CODEC_FLAG2_NO_OUTPUT)
        return 0;
    if (s->context) {
        for (i = 0; i < count; i++) {
            LOAD4;
            s->stats[0][y0]++;
            put_bits(&s->pb, s->len[0][y0], s->bits[0][y0]);
            s->stats[1][u0]++;
            put_bits(&s->pb, s->len[1][u0], s->bits[1][u0]);
            s->stats[0][y1]++;
            put_bits(&s->pb, s->len[0][y1], s->bits[0][y1]);
            s->stats[2][v0]++;
            put_bits(&s->pb, s->len[2][v0], s->bits[2][v0]);
        }
    } else {
        for(i = 0; i < count; i++) {
            LOAD4;
            put_bits(&s->pb, s->len[0][y0], s->bits[0][y0]);
            put_bits(&s->pb, s->len[1][u0], s->bits[1][u0]);
            put_bits(&s->pb, s->len[0][y1], s->bits[0][y1]);
            put_bits(&s->pb, s->len[2][v0], s->bits[2][v0]);
        }
    }
    return 0;
}
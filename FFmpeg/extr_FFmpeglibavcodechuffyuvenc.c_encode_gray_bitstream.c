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
 int AV_CODEC_FLAG2_NO_OUTPUT ; 
 int AV_CODEC_FLAG_PASS1 ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  put_bits (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int put_bits_count (TYPE_2__*) ; 

__attribute__((used)) static int encode_gray_bitstream(HYuvContext *s, int count)
{
    int i;

    if (s->pb.buf_end - s->pb.buf - (put_bits_count(&s->pb) >> 3) < 4 * count) {
        av_log(s->avctx, AV_LOG_ERROR, "encoded frame too large\n");
        return -1;
    }

#define LOAD2\
            int y0 = s->temp[0][2 * i];\
            int y1 = s->temp[0][2 * i + 1];
#define STAT2\
            s->stats[0][y0]++;\
            s->stats[0][y1]++;
#define WRITE2\
            put_bits(&s->pb, s->len[0][y0], s->bits[0][y0]);\
            put_bits(&s->pb, s->len[0][y1], s->bits[0][y1]);

    count /= 2;

    if (s->flags & AV_CODEC_FLAG_PASS1) {
        for (i = 0; i < count; i++) {
            LOAD2;
            STAT2;
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
    } else {
        for (i = 0; i < count; i++) {
            LOAD2;
            WRITE2;
        }
    }
    return 0;
}
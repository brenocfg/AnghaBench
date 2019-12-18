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
typedef  int uint16_t ;
typedef  unsigned int int16_t ;
struct TYPE_6__ {int* permutated; } ;
struct TYPE_7__ {int /*<<< orphan*/  gb; int /*<<< orphan*/  avctx; TYPE_2__ scantable; TYPE_1__** vlcs; } ;
struct TYPE_5__ {int /*<<< orphan*/  table; } ;
typedef  TYPE_3__ MJpegDecodeContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  CLOSE_READER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int GET_CACHE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GET_VLC (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  LAST_SKIP_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int MIN_CACHE_BITS ; 
 int NEG_USR32 (int,int) ; 
 int /*<<< orphan*/  OPEN_READER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UPDATE_CACHE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  re ; 

__attribute__((used)) static int decode_block_progressive(MJpegDecodeContext *s, int16_t *block,
                                    uint8_t *last_nnz, int ac_index,
                                    uint16_t *quant_matrix,
                                    int ss, int se, int Al, int *EOBRUN)
{
    int code, i, j, val, run;
    unsigned level;

    if (*EOBRUN) {
        (*EOBRUN)--;
        return 0;
    }

    {
        OPEN_READER(re, &s->gb);
        for (i = ss; ; i++) {
            UPDATE_CACHE(re, &s->gb);
            GET_VLC(code, re, &s->gb, s->vlcs[2][ac_index].table, 9, 2);

            run = ((unsigned) code) >> 4;
            code &= 0xF;
            if (code) {
                i += run;
                if (code > MIN_CACHE_BITS - 16)
                    UPDATE_CACHE(re, &s->gb);

                {
                    int cache = GET_CACHE(re, &s->gb);
                    int sign  = (~cache) >> 31;
                    level     = (NEG_USR32(sign ^ cache,code) ^ sign) - sign;
                }

                LAST_SKIP_BITS(re, &s->gb, code);

                if (i >= se) {
                    if (i == se) {
                        j = s->scantable.permutated[se];
                        block[j] = level * (quant_matrix[se] << Al);
                        break;
                    }
                    av_log(s->avctx, AV_LOG_ERROR, "error count: %d\n", i);
                    return AVERROR_INVALIDDATA;
                }
                j = s->scantable.permutated[i];
                block[j] = level * (quant_matrix[i] << Al);
            } else {
                if (run == 0xF) {// ZRL - skip 15 coefficients
                    i += 15;
                    if (i >= se) {
                        av_log(s->avctx, AV_LOG_ERROR, "ZRL overflow: %d\n", i);
                        return AVERROR_INVALIDDATA;
                    }
                } else {
                    val = (1 << run);
                    if (run) {
                        UPDATE_CACHE(re, &s->gb);
                        val += NEG_USR32(GET_CACHE(re, &s->gb), run);
                        LAST_SKIP_BITS(re, &s->gb, run);
                    }
                    *EOBRUN = val - 1;
                    break;
                }
            }
        }
        CLOSE_READER(re, &s->gb);
    }

    if (i > *last_nnz)
        *last_nnz = i;

    return 0;
}
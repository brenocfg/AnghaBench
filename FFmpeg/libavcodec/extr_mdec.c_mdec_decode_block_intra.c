#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int int16_t ;
struct TYPE_6__ {int* permutated; } ;
struct TYPE_8__ {int* quant_matrix; int qscale; int version; int* last_dc; int* block_last_index; int /*<<< orphan*/  gb; int /*<<< orphan*/  mb_y; int /*<<< orphan*/  mb_x; int /*<<< orphan*/  avctx; TYPE_1__ scantable; } ;
struct TYPE_7__ {int /*<<< orphan*/ * rl_vlc; } ;
typedef  TYPE_2__ RLTable ;
typedef  TYPE_3__ MDECContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  CLOSE_READER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GET_RL_VLC (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LAST_SKIP_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OPEN_READER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int SHOW_SBITS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int SHOW_UBITS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SKIP_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TEX_VLC_BITS ; 
 int /*<<< orphan*/  UPDATE_CACHE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int decode_dc (int /*<<< orphan*/ *,int) ; 
 TYPE_2__ ff_rl_mpeg1 ; 
 int get_sbits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  re ; 

__attribute__((used)) static inline int mdec_decode_block_intra(MDECContext *a, int16_t *block, int n)
{
    int level, diff, i, j, run;
    int component;
    RLTable *rl = &ff_rl_mpeg1;
    uint8_t * const scantable = a->scantable.permutated;
    const uint16_t *quant_matrix = a->quant_matrix;
    const int qscale = a->qscale;

    /* DC coefficient */
    if (a->version == 2) {
        block[0] = 2 * get_sbits(&a->gb, 10) + 1024;
    } else {
        component = (n <= 3 ? 0 : n - 4 + 1);
        diff = decode_dc(&a->gb, component);
        if (diff >= 0xffff)
            return AVERROR_INVALIDDATA;
        a->last_dc[component] += diff;
        block[0] = a->last_dc[component] * (1 << 3);
    }

    i = 0;
    {
        OPEN_READER(re, &a->gb);
        /* now quantify & encode AC coefficients */
        for (;;) {
            UPDATE_CACHE(re, &a->gb);
            GET_RL_VLC(level, run, re, &a->gb, rl->rl_vlc[0], TEX_VLC_BITS, 2, 0);

            if (level == 127) {
                break;
            } else if (level != 0) {
                i += run;
                if (i > 63) {
                    av_log(a->avctx, AV_LOG_ERROR,
                           "ac-tex damaged at %d %d\n", a->mb_x, a->mb_y);
                    return AVERROR_INVALIDDATA;
                }
                j     = scantable[i];
                level = (level * qscale * quant_matrix[j]) >> 3;
                level = (level ^ SHOW_SBITS(re, &a->gb, 1)) - SHOW_SBITS(re, &a->gb, 1);
                LAST_SKIP_BITS(re, &a->gb, 1);
            } else {
                /* escape */
                run = SHOW_UBITS(re, &a->gb, 6)+1; LAST_SKIP_BITS(re, &a->gb, 6);
                UPDATE_CACHE(re, &a->gb);
                level = SHOW_SBITS(re, &a->gb, 10); SKIP_BITS(re, &a->gb, 10);
                i += run;
                if (i > 63) {
                    av_log(a->avctx, AV_LOG_ERROR,
                           "ac-tex damaged at %d %d\n", a->mb_x, a->mb_y);
                    return AVERROR_INVALIDDATA;
                }
                j = scantable[i];
                if (level < 0) {
                    level = -level;
                    level = (level * (unsigned)qscale * quant_matrix[j]) >> 3;
                    level = (level - 1) | 1;
                    level = -level;
                } else {
                    level = (level * (unsigned)qscale * quant_matrix[j]) >> 3;
                    level = (level - 1) | 1;
                }
            }

            block[j] = level;
        }
        CLOSE_READER(re, &a->gb);
    }
    a->block_last_index[n] = i;
    return 0;
}
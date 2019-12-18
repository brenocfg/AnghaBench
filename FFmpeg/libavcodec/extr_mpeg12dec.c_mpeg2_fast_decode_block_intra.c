#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int int16_t ;
struct TYPE_8__ {int* permutated; } ;
struct TYPE_10__ {int qscale; int* intra_matrix; int* chroma_intra_matrix; int* last_dc; int intra_dc_precision; int* block_last_index; int /*<<< orphan*/  gb; scalar_t__ intra_vlc_format; TYPE_1__ intra_scantable; } ;
struct TYPE_9__ {int /*<<< orphan*/ * rl_vlc; } ;
typedef  TYPE_2__ RLTable ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  CLOSE_READER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GET_RL_VLC (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LAST_SKIP_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OPEN_READER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int SHOW_SBITS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int SHOW_UBITS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SKIP_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TEX_VLC_BITS ; 
 int /*<<< orphan*/  UPDATE_CACHE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_scantable_index (TYPE_3__*,int) ; 
 int decode_dc (int /*<<< orphan*/ *,int) ; 
 TYPE_2__ ff_rl_mpeg1 ; 
 TYPE_2__ ff_rl_mpeg2 ; 
 int /*<<< orphan*/  re ; 

__attribute__((used)) static inline int mpeg2_fast_decode_block_intra(MpegEncContext *s,
                                                int16_t *block, int n)
{
    int level, dc, diff, i, j, run;
    int component;
    RLTable *rl;
    uint8_t *const scantable = s->intra_scantable.permutated;
    const uint16_t *quant_matrix;
    const int qscale = s->qscale;

    /* DC coefficient */
    if (n < 4) {
        quant_matrix = s->intra_matrix;
        component    = 0;
    } else {
        quant_matrix = s->chroma_intra_matrix;
        component    = (n & 1) + 1;
    }
    diff = decode_dc(&s->gb, component);
    if (diff >= 0xffff)
        return AVERROR_INVALIDDATA;
    dc = s->last_dc[component];
    dc += diff;
    s->last_dc[component] = dc;
    block[0] = dc << (3 - s->intra_dc_precision);
    i = 0;
    if (s->intra_vlc_format)
        rl = &ff_rl_mpeg2;
    else
        rl = &ff_rl_mpeg1;

    {
        OPEN_READER(re, &s->gb);
        /* now quantify & encode AC coefficients */
        for (;;) {
            UPDATE_CACHE(re, &s->gb);
            GET_RL_VLC(level, run, re, &s->gb, rl->rl_vlc[0],
                       TEX_VLC_BITS, 2, 0);

            if (level >= 64 || i > 63) {
                break;
            } else if (level != 0) {
                i += run;
                j = scantable[i];
                level = (level * qscale * quant_matrix[j]) >> 4;
                level = (level ^ SHOW_SBITS(re, &s->gb, 1)) -
                        SHOW_SBITS(re, &s->gb, 1);
                LAST_SKIP_BITS(re, &s->gb, 1);
            } else {
                /* escape */
                run = SHOW_UBITS(re, &s->gb, 6) + 1;
                LAST_SKIP_BITS(re, &s->gb, 6);
                UPDATE_CACHE(re, &s->gb);
                level = SHOW_SBITS(re, &s->gb, 12);
                SKIP_BITS(re, &s->gb, 12);
                i += run;
                j = scantable[i];
                if (level < 0) {
                    level = (-level * qscale * quant_matrix[j]) >> 4;
                    level = -level;
                } else {
                    level = (level * qscale * quant_matrix[j]) >> 4;
                }
            }

            block[j] = level;
        }
        CLOSE_READER(re, &s->gb);
    }

    check_scantable_index(s, i);

    s->block_last_index[n] = i;
    return 0;
}
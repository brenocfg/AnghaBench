#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ int32_t ;
typedef  int int16_t ;
struct TYPE_7__ {int* permutated; } ;
struct TYPE_9__ {int qscale; int* block_last_index; int /*<<< orphan*/  gb; TYPE_1__ intra_scantable; } ;
struct TYPE_8__ {int /*<<< orphan*/ * rl_vlc; } ;
typedef  TYPE_2__ RLTable ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSE_READER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int GET_CACHE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GET_RL_VLC (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LAST_SKIP_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int MAX_INDEX ; 
 int /*<<< orphan*/  OPEN_READER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int SHOW_SBITS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int SHOW_UBITS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SKIP_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TEX_VLC_BITS ; 
 int /*<<< orphan*/  UPDATE_CACHE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_scantable_index (TYPE_3__*,int) ; 
 TYPE_2__ ff_rl_mpeg1 ; 
 int /*<<< orphan*/  re ; 

__attribute__((used)) static inline int mpeg2_fast_decode_block_non_intra(MpegEncContext *s,
                                                    int16_t *block, int n)
{
    int level, i, j, run;
    RLTable *rl              = &ff_rl_mpeg1;
    uint8_t *const scantable = s->intra_scantable.permutated;
    const int qscale         = s->qscale;
    OPEN_READER(re, &s->gb);
    i = -1;

    // special case for first coefficient, no need to add second VLC table
    UPDATE_CACHE(re, &s->gb);
    if (((int32_t) GET_CACHE(re, &s->gb)) < 0) {
        level = (3 * qscale) >> 1;
        if (GET_CACHE(re, &s->gb) & 0x40000000)
            level = -level;
        block[0] = level;
        i++;
        SKIP_BITS(re, &s->gb, 2);
        if (((int32_t) GET_CACHE(re, &s->gb)) <= (int32_t) 0xBFFFFFFF)
            goto end;
    }

    /* now quantify & encode AC coefficients */
    for (;;) {
        GET_RL_VLC(level, run, re, &s->gb, rl->rl_vlc[0], TEX_VLC_BITS, 2, 0);

        if (level != 0) {
            i += run;
            if (i > MAX_INDEX)
                break;
            j = scantable[i];
            level = ((level * 2 + 1) * qscale) >> 1;
            level = (level ^ SHOW_SBITS(re, &s->gb, 1)) -
                    SHOW_SBITS(re, &s->gb, 1);
            SKIP_BITS(re, &s->gb, 1);
        } else {
            /* escape */
            run = SHOW_UBITS(re, &s->gb, 6) + 1;
            LAST_SKIP_BITS(re, &s->gb, 6);
            UPDATE_CACHE(re, &s->gb);
            level = SHOW_SBITS(re, &s->gb, 12);
            SKIP_BITS(re, &s->gb, 12);

            i += run;
            if (i > MAX_INDEX)
                break;
            j = scantable[i];
            if (level < 0) {
                level = ((-level * 2 + 1) * qscale) >> 1;
                level = -level;
            } else {
                level = ((level * 2 + 1) * qscale) >> 1;
            }
        }

        block[j] = level;
        if (((int32_t) GET_CACHE(re, &s->gb)) <= (int32_t) 0xBFFFFFFF || i > 63)
            break;

        UPDATE_CACHE(re, &s->gb);
    }
end:
    LAST_SKIP_BITS(re, &s->gb, 2);
    CLOSE_READER(re, &s->gb);

    check_scantable_index(s, i);

    s->block_last_index[n] = i;
    return 0;
}
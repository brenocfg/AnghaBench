#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int int16_t ;
struct TYPE_7__ {int* permutated; } ;
struct TYPE_9__ {int* block_last_index; int /*<<< orphan*/  gb; int /*<<< orphan*/  mb_y; int /*<<< orphan*/  mb_x; int /*<<< orphan*/  avctx; scalar_t__ mb_intra; TYPE_1__ intra_scantable; } ;
struct TYPE_10__ {TYPE_3__ s; } ;
struct TYPE_8__ {int /*<<< orphan*/ * rl_vlc; } ;
typedef  TYPE_2__ RLTable ;
typedef  TYPE_3__ MpegEncContext ;
typedef  TYPE_4__ H261Context ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  CLOSE_READER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GET_RL_VLC (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPEN_READER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int SHOW_SBITS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int SHOW_UBITS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SKIP_CACHE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SKIP_COUNTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TCOEFF_VLC_BITS ; 
 int /*<<< orphan*/  UPDATE_CACHE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,...) ; 
 TYPE_2__ ff_h261_rl_tcoeff ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  re ; 
 int show_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int h261_decode_block(H261Context *h, int16_t *block, int n, int coded)
{
    MpegEncContext *const s = &h->s;
    int level, i, j, run;
    RLTable *rl = &ff_h261_rl_tcoeff;
    const uint8_t *scan_table;

    /* For the variable length encoding there are two code tables, one being
     * used for the first transmitted LEVEL in INTER, INTER + MC and
     * INTER + MC + FIL blocks, the second for all other LEVELs except the
     * first one in INTRA blocks which is fixed length coded with 8 bits.
     * NOTE: The two code tables only differ in one VLC so we handle that
     * manually. */
    scan_table = s->intra_scantable.permutated;
    if (s->mb_intra) {
        /* DC coef */
        level = get_bits(&s->gb, 8);
        // 0 (00000000b) and -128 (10000000b) are FORBIDDEN
        if ((level & 0x7F) == 0) {
            av_log(s->avctx, AV_LOG_ERROR, "illegal dc %d at %d %d\n",
                   level, s->mb_x, s->mb_y);
            return -1;
        }
        /* The code 1000 0000 is not used, the reconstruction level of 1024
         * being coded as 1111 1111. */
        if (level == 255)
            level = 128;
        block[0] = level;
        i        = 1;
    } else if (coded) {
        // Run  Level   Code
        // EOB          Not possible for first level when cbp is available (that's why the table is different)
        // 0    1       1s
        // *    *       0*
        int check = show_bits(&s->gb, 2);
        i = 0;
        if (check & 0x2) {
            skip_bits(&s->gb, 2);
            block[0] = (check & 0x1) ? -1 : 1;
            i        = 1;
        }
    } else {
        i = 0;
    }
    if (!coded) {
        s->block_last_index[n] = i - 1;
        return 0;
    }
    {
    OPEN_READER(re, &s->gb);
    i--; // offset by -1 to allow direct indexing of scan_table
    for (;;) {
        UPDATE_CACHE(re, &s->gb);
        GET_RL_VLC(level, run, re, &s->gb, rl->rl_vlc[0], TCOEFF_VLC_BITS, 2, 0);
        if (run == 66) {
            if (level) {
                CLOSE_READER(re, &s->gb);
                av_log(s->avctx, AV_LOG_ERROR, "illegal ac vlc code at %dx%d\n",
                       s->mb_x, s->mb_y);
                return -1;
            }
            /* escape */
            /* The remaining combinations of (run, level) are encoded with a
             * 20-bit word consisting of 6 bits escape, 6 bits run and 8 bits
             * level. */
            run   = SHOW_UBITS(re, &s->gb, 6) + 1;
            SKIP_CACHE(re, &s->gb, 6);
            level = SHOW_SBITS(re, &s->gb, 8);
            SKIP_COUNTER(re, &s->gb, 6 + 8);
        } else if (level == 0) {
            break;
        } else {
            if (SHOW_UBITS(re, &s->gb, 1))
                level = -level;
            SKIP_COUNTER(re, &s->gb, 1);
        }
        i += run;
        if (i >= 64) {
            CLOSE_READER(re, &s->gb);
            av_log(s->avctx, AV_LOG_ERROR, "run overflow at %dx%d\n",
                   s->mb_x, s->mb_y);
            return -1;
        }
        j        = scan_table[i];
        block[j] = level;
    }
    CLOSE_READER(re, &s->gb);
    }
    s->block_last_index[n] = i;
    return 0;
}
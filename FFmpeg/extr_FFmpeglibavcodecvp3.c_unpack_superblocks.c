#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  table; } ;
struct TYPE_8__ {int /*<<< orphan*/  table; } ;
struct TYPE_9__ {int u_superblock_start; int v_superblock_start; int* superblock_coding; int superblock_count; int* macroblock_coding; int macroblock_count; int** coded_fragment_list; int* kf_coded_fragment_list; int* nkf_coded_fragment_list; int c_superblock_count; int y_superblock_count; int* num_kf_coded_fragment; int* superblock_fragments; int** num_coded_frags; scalar_t__ total_num_coded_frags; TYPE_2__* all_fragments; TYPE_1__ fragment_run_length_vlc; scalar_t__ keyframe; int /*<<< orphan*/  avctx; TYPE_3__ superblock_run_length_vlc; scalar_t__ theora; } ;
typedef  TYPE_4__ Vp3DecodeContext ;
struct TYPE_7__ {int coding_method; } ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int MAXIMUM_LONG_BIT_RUN ; 
 int MODE_COPY ; 
 int MODE_INTER_NO_MV ; 
 int SB_FULLY_CODED ; 
 int SB_NOT_CODED ; 
 int SB_PARTIALLY_CODED ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 

__attribute__((used)) static int unpack_superblocks(Vp3DecodeContext *s, GetBitContext *gb)
{
    int superblock_starts[3] = {
        0, s->u_superblock_start, s->v_superblock_start
    };
    int bit = 0;
    int current_superblock = 0;
    int current_run = 0;
    int num_partial_superblocks = 0;

    int i, j;
    int current_fragment;
    int plane;
    int plane0_num_coded_frags = 0;

    if (s->keyframe) {
        memset(s->superblock_coding, SB_FULLY_CODED, s->superblock_count);
    } else {
        /* unpack the list of partially-coded superblocks */
        bit         = get_bits1(gb) ^ 1;
        current_run = 0;

        while (current_superblock < s->superblock_count && get_bits_left(gb) > 0) {
            if (s->theora && current_run == MAXIMUM_LONG_BIT_RUN)
                bit = get_bits1(gb);
            else
                bit ^= 1;

            current_run = get_vlc2(gb, s->superblock_run_length_vlc.table,
                                   6, 2) + 1;
            if (current_run == 34)
                current_run += get_bits(gb, 12);

            if (current_run > s->superblock_count - current_superblock) {
                av_log(s->avctx, AV_LOG_ERROR,
                       "Invalid partially coded superblock run length\n");
                return -1;
            }

            memset(s->superblock_coding + current_superblock, bit, current_run);

            current_superblock += current_run;
            if (bit)
                num_partial_superblocks += current_run;
        }

        /* unpack the list of fully coded superblocks if any of the blocks were
         * not marked as partially coded in the previous step */
        if (num_partial_superblocks < s->superblock_count) {
            int superblocks_decoded = 0;

            current_superblock = 0;
            bit                = get_bits1(gb) ^ 1;
            current_run        = 0;

            while (superblocks_decoded < s->superblock_count - num_partial_superblocks &&
                   get_bits_left(gb) > 0) {
                if (s->theora && current_run == MAXIMUM_LONG_BIT_RUN)
                    bit = get_bits1(gb);
                else
                    bit ^= 1;

                current_run = get_vlc2(gb, s->superblock_run_length_vlc.table,
                                       6, 2) + 1;
                if (current_run == 34)
                    current_run += get_bits(gb, 12);

                for (j = 0; j < current_run; current_superblock++) {
                    if (current_superblock >= s->superblock_count) {
                        av_log(s->avctx, AV_LOG_ERROR,
                               "Invalid fully coded superblock run length\n");
                        return -1;
                    }

                    /* skip any superblocks already marked as partially coded */
                    if (s->superblock_coding[current_superblock] == SB_NOT_CODED) {
                        s->superblock_coding[current_superblock] = 2 * bit;
                        j++;
                    }
                }
                superblocks_decoded += current_run;
            }
        }

        /* if there were partial blocks, initialize bitstream for
         * unpacking fragment codings */
        if (num_partial_superblocks) {
            current_run = 0;
            bit         = get_bits1(gb);
            /* toggle the bit because as soon as the first run length is
             * fetched the bit will be toggled again */
            bit ^= 1;
        }
    }

    /* figure out which fragments are coded; iterate through each
     * superblock (all planes) */
    s->total_num_coded_frags = 0;
    memset(s->macroblock_coding, MODE_COPY, s->macroblock_count);

    s->coded_fragment_list[0] = s->keyframe ? s->kf_coded_fragment_list
                                            : s->nkf_coded_fragment_list;

    for (plane = 0; plane < 3; plane++) {
        int sb_start = superblock_starts[plane];
        int sb_end   = sb_start + (plane ? s->c_superblock_count
                                         : s->y_superblock_count);
        int num_coded_frags = 0;

        if (s->keyframe) {
            if (s->num_kf_coded_fragment[plane] == -1) {
                for (i = sb_start; i < sb_end; i++) {
                    /* iterate through all 16 fragments in a superblock */
                    for (j = 0; j < 16; j++) {
                        /* if the fragment is in bounds, check its coding status */
                        current_fragment = s->superblock_fragments[i * 16 + j];
                        if (current_fragment != -1) {
                            s->coded_fragment_list[plane][num_coded_frags++] =
                                current_fragment;
                        }
                    }
                }
                s->num_kf_coded_fragment[plane] = num_coded_frags;
            } else
                num_coded_frags = s->num_kf_coded_fragment[plane];
        } else {
            for (i = sb_start; i < sb_end && get_bits_left(gb) > 0; i++) {
                if (get_bits_left(gb) < plane0_num_coded_frags >> 2) {
                    return AVERROR_INVALIDDATA;
                }
                /* iterate through all 16 fragments in a superblock */
                for (j = 0; j < 16; j++) {
                    /* if the fragment is in bounds, check its coding status */
                    current_fragment = s->superblock_fragments[i * 16 + j];
                    if (current_fragment != -1) {
                        int coded = s->superblock_coding[i];

                        if (coded == SB_PARTIALLY_CODED) {
                            /* fragment may or may not be coded; this is the case
                             * that cares about the fragment coding runs */
                            if (current_run-- == 0) {
                                bit        ^= 1;
                                current_run = get_vlc2(gb, s->fragment_run_length_vlc.table, 5, 2);
                            }
                            coded = bit;
                        }

                        if (coded) {
                            /* default mode; actual mode will be decoded in
                             * the next phase */
                            s->all_fragments[current_fragment].coding_method =
                                MODE_INTER_NO_MV;
                            s->coded_fragment_list[plane][num_coded_frags++] =
                                current_fragment;
                        } else {
                            /* not coded; copy this fragment from the prior frame */
                            s->all_fragments[current_fragment].coding_method =
                                MODE_COPY;
                        }
                    }
                }
            }
        }
        if (!plane)
            plane0_num_coded_frags = num_coded_frags;
        s->total_num_coded_frags += num_coded_frags;
        for (i = 0; i < 64; i++)
            s->num_coded_frags[plane][i] = num_coded_frags;
        if (plane < 2)
            s->coded_fragment_list[plane + 1] = s->coded_fragment_list[plane] +
                                                num_coded_frags;
    }
    return 0;
}
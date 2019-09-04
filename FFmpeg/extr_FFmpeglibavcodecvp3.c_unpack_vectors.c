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
struct TYPE_6__ {int /*<<< orphan*/  table; } ;
struct TYPE_7__ {int y_superblock_height; int y_superblock_width; int macroblock_width; int macroblock_height; int* macroblock_coding; int* fragment_width; int*** motion_val; scalar_t__ chroma_x_shift; scalar_t__ chroma_y_shift; TYPE_2__ motion_vector_vlc; TYPE_1__* all_fragments; scalar_t__ keyframe; } ;
typedef  TYPE_3__ Vp3DecodeContext ;
struct TYPE_5__ {int coding_method; } ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int BLOCK_X ; 
 int BLOCK_Y ; 
 int MODE_COPY ; 
#define  MODE_GOLDEN_MV 132 
#define  MODE_INTER_FOURMV 131 
#define  MODE_INTER_LAST_MV 130 
#define  MODE_INTER_PLUS_MV 129 
#define  MODE_INTER_PRIOR_LAST 128 
 int RSHIFT (int,int) ; 
 int* fixed_motion_vector_table ; 
 size_t get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 scalar_t__ get_bits_left (int /*<<< orphan*/ *) ; 
 size_t get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int* motion_vector_table ; 

__attribute__((used)) static int unpack_vectors(Vp3DecodeContext *s, GetBitContext *gb)
{
    int j, k, sb_x, sb_y;
    int coding_mode;
    int motion_x[4];
    int motion_y[4];
    int last_motion_x = 0;
    int last_motion_y = 0;
    int prior_last_motion_x = 0;
    int prior_last_motion_y = 0;
    int current_macroblock;
    int current_fragment;
    int frag;

    if (s->keyframe)
        return 0;

    /* coding mode 0 is the VLC scheme; 1 is the fixed code scheme */
    coding_mode = get_bits1(gb);

    /* iterate through all of the macroblocks that contain 1 or more
     * coded fragments */
    for (sb_y = 0; sb_y < s->y_superblock_height; sb_y++) {
        for (sb_x = 0; sb_x < s->y_superblock_width; sb_x++) {
            if (get_bits_left(gb) <= 0)
                return -1;

            for (j = 0; j < 4; j++) {
                int mb_x = 2 * sb_x + (j >> 1);
                int mb_y = 2 * sb_y + (((j >> 1) + j) & 1);
                current_macroblock = mb_y * s->macroblock_width + mb_x;

                if (mb_x >= s->macroblock_width  ||
                    mb_y >= s->macroblock_height ||
                    s->macroblock_coding[current_macroblock] == MODE_COPY)
                    continue;

                switch (s->macroblock_coding[current_macroblock]) {
                case MODE_INTER_PLUS_MV:
                case MODE_GOLDEN_MV:
                    /* all 6 fragments use the same motion vector */
                    if (coding_mode == 0) {
                        motion_x[0] = motion_vector_table[get_vlc2(gb, s->motion_vector_vlc.table, 6, 2)];
                        motion_y[0] = motion_vector_table[get_vlc2(gb, s->motion_vector_vlc.table, 6, 2)];
                    } else {
                        motion_x[0] = fixed_motion_vector_table[get_bits(gb, 6)];
                        motion_y[0] = fixed_motion_vector_table[get_bits(gb, 6)];
                    }

                    /* vector maintenance, only on MODE_INTER_PLUS_MV */
                    if (s->macroblock_coding[current_macroblock] == MODE_INTER_PLUS_MV) {
                        prior_last_motion_x = last_motion_x;
                        prior_last_motion_y = last_motion_y;
                        last_motion_x       = motion_x[0];
                        last_motion_y       = motion_y[0];
                    }
                    break;

                case MODE_INTER_FOURMV:
                    /* vector maintenance */
                    prior_last_motion_x = last_motion_x;
                    prior_last_motion_y = last_motion_y;

                    /* fetch 4 vectors from the bitstream, one for each
                     * Y fragment, then average for the C fragment vectors */
                    for (k = 0; k < 4; k++) {
                        current_fragment = BLOCK_Y * s->fragment_width[0] + BLOCK_X;
                        if (s->all_fragments[current_fragment].coding_method != MODE_COPY) {
                            if (coding_mode == 0) {
                                motion_x[k] = motion_vector_table[get_vlc2(gb, s->motion_vector_vlc.table, 6, 2)];
                                motion_y[k] = motion_vector_table[get_vlc2(gb, s->motion_vector_vlc.table, 6, 2)];
                            } else {
                                motion_x[k] = fixed_motion_vector_table[get_bits(gb, 6)];
                                motion_y[k] = fixed_motion_vector_table[get_bits(gb, 6)];
                            }
                            last_motion_x = motion_x[k];
                            last_motion_y = motion_y[k];
                        } else {
                            motion_x[k] = 0;
                            motion_y[k] = 0;
                        }
                    }
                    break;

                case MODE_INTER_LAST_MV:
                    /* all 6 fragments use the last motion vector */
                    motion_x[0] = last_motion_x;
                    motion_y[0] = last_motion_y;

                    /* no vector maintenance (last vector remains the
                     * last vector) */
                    break;

                case MODE_INTER_PRIOR_LAST:
                    /* all 6 fragments use the motion vector prior to the
                     * last motion vector */
                    motion_x[0] = prior_last_motion_x;
                    motion_y[0] = prior_last_motion_y;

                    /* vector maintenance */
                    prior_last_motion_x = last_motion_x;
                    prior_last_motion_y = last_motion_y;
                    last_motion_x       = motion_x[0];
                    last_motion_y       = motion_y[0];
                    break;

                default:
                    /* covers intra, inter without MV, golden without MV */
                    motion_x[0] = 0;
                    motion_y[0] = 0;

                    /* no vector maintenance */
                    break;
                }

                /* assign the motion vectors to the correct fragments */
                for (k = 0; k < 4; k++) {
                    current_fragment =
                        BLOCK_Y * s->fragment_width[0] + BLOCK_X;
                    if (s->macroblock_coding[current_macroblock] == MODE_INTER_FOURMV) {
                        s->motion_val[0][current_fragment][0] = motion_x[k];
                        s->motion_val[0][current_fragment][1] = motion_y[k];
                    } else {
                        s->motion_val[0][current_fragment][0] = motion_x[0];
                        s->motion_val[0][current_fragment][1] = motion_y[0];
                    }
                }

                if (s->chroma_y_shift) {
                    if (s->macroblock_coding[current_macroblock] == MODE_INTER_FOURMV) {
                        motion_x[0] = RSHIFT(motion_x[0] + motion_x[1] +
                                             motion_x[2] + motion_x[3], 2);
                        motion_y[0] = RSHIFT(motion_y[0] + motion_y[1] +
                                             motion_y[2] + motion_y[3], 2);
                    }
                    motion_x[0] = (motion_x[0] >> 1) | (motion_x[0] & 1);
                    motion_y[0] = (motion_y[0] >> 1) | (motion_y[0] & 1);
                    frag = mb_y * s->fragment_width[1] + mb_x;
                    s->motion_val[1][frag][0] = motion_x[0];
                    s->motion_val[1][frag][1] = motion_y[0];
                } else if (s->chroma_x_shift) {
                    if (s->macroblock_coding[current_macroblock] == MODE_INTER_FOURMV) {
                        motion_x[0] = RSHIFT(motion_x[0] + motion_x[1], 1);
                        motion_y[0] = RSHIFT(motion_y[0] + motion_y[1], 1);
                        motion_x[1] = RSHIFT(motion_x[2] + motion_x[3], 1);
                        motion_y[1] = RSHIFT(motion_y[2] + motion_y[3], 1);
                    } else {
                        motion_x[1] = motion_x[0];
                        motion_y[1] = motion_y[0];
                    }
                    motion_x[0] = (motion_x[0] >> 1) | (motion_x[0] & 1);
                    motion_x[1] = (motion_x[1] >> 1) | (motion_x[1] & 1);

                    frag = 2 * mb_y * s->fragment_width[1] + mb_x;
                    for (k = 0; k < 2; k++) {
                        s->motion_val[1][frag][0] = motion_x[k];
                        s->motion_val[1][frag][1] = motion_y[k];
                        frag += s->fragment_width[1];
                    }
                } else {
                    for (k = 0; k < 4; k++) {
                        frag = BLOCK_Y * s->fragment_width[1] + BLOCK_X;
                        if (s->macroblock_coding[current_macroblock] == MODE_INTER_FOURMV) {
                            s->motion_val[1][frag][0] = motion_x[k];
                            s->motion_val[1][frag][1] = motion_y[k];
                        } else {
                            s->motion_val[1][frag][0] = motion_x[0];
                            s->motion_val[1][frag][1] = motion_y[0];
                        }
                    }
                }
            }
        }
    }

    return 0;
}
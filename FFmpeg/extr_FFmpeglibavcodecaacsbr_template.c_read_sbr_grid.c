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
struct TYPE_9__ {int /*<<< orphan*/  avctx; } ;
struct TYPE_8__ {unsigned int bs_num_env; int t_env_num_env_old; int* t_env; int bs_frame_class; int bs_num_noise; scalar_t__* t_q; int* e_a; void** bs_freq_res; int /*<<< orphan*/  bs_amp_res; } ;
struct TYPE_7__ {int /*<<< orphan*/  bs_amp_res_header; } ;
typedef  TYPE_1__ SpectralBandReplication ;
typedef  TYPE_2__ SBRData ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_3__ AACContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int FFMAX (int,int) ; 
#define  FIXFIX 131 
#define  FIXVAR 130 
#define  VARFIX 129 
#define  VARVAR 128 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int* ceil_log2 ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_bits1_vector (int /*<<< orphan*/ *,void**,size_t) ; 

__attribute__((used)) static int read_sbr_grid(AACContext *ac, SpectralBandReplication *sbr,
                         GetBitContext *gb, SBRData *ch_data)
{
    int i;
    int bs_pointer = 0;
    // frameLengthFlag ? 15 : 16; 960 sample length frames unsupported; this value is numTimeSlots
    int abs_bord_trail = 16;
    int num_rel_lead, num_rel_trail;
    unsigned bs_num_env_old = ch_data->bs_num_env;
    int bs_frame_class, bs_num_env;

    ch_data->bs_freq_res[0] = ch_data->bs_freq_res[ch_data->bs_num_env];
    ch_data->bs_amp_res = sbr->bs_amp_res_header;
    ch_data->t_env_num_env_old = ch_data->t_env[bs_num_env_old];

    switch (bs_frame_class = get_bits(gb, 2)) {
    case FIXFIX:
        bs_num_env = 1 << get_bits(gb, 2);
        if (bs_num_env > 4) {
            av_log(ac->avctx, AV_LOG_ERROR,
                   "Invalid bitstream, too many SBR envelopes in FIXFIX type SBR frame: %d\n",
                   bs_num_env);
            return -1;
        }
        ch_data->bs_num_env = bs_num_env;
        num_rel_lead                        = ch_data->bs_num_env - 1;
        if (ch_data->bs_num_env == 1)
            ch_data->bs_amp_res = 0;


        ch_data->t_env[0]                   = 0;
        ch_data->t_env[ch_data->bs_num_env] = abs_bord_trail;

        abs_bord_trail = (abs_bord_trail + (ch_data->bs_num_env >> 1)) /
                   ch_data->bs_num_env;
        for (i = 0; i < num_rel_lead; i++)
            ch_data->t_env[i + 1] = ch_data->t_env[i] + abs_bord_trail;

        ch_data->bs_freq_res[1] = get_bits1(gb);
        for (i = 1; i < ch_data->bs_num_env; i++)
            ch_data->bs_freq_res[i + 1] = ch_data->bs_freq_res[1];
        break;
    case FIXVAR:
        abs_bord_trail                     += get_bits(gb, 2);
        num_rel_trail                       = get_bits(gb, 2);
        ch_data->bs_num_env                 = num_rel_trail + 1;
        ch_data->t_env[0]                   = 0;
        ch_data->t_env[ch_data->bs_num_env] = abs_bord_trail;

        for (i = 0; i < num_rel_trail; i++)
            ch_data->t_env[ch_data->bs_num_env - 1 - i] =
                ch_data->t_env[ch_data->bs_num_env - i] - 2 * get_bits(gb, 2) - 2;

        bs_pointer = get_bits(gb, ceil_log2[ch_data->bs_num_env]);

        for (i = 0; i < ch_data->bs_num_env; i++)
            ch_data->bs_freq_res[ch_data->bs_num_env - i] = get_bits1(gb);
        break;
    case VARFIX:
        ch_data->t_env[0]                   = get_bits(gb, 2);
        num_rel_lead                        = get_bits(gb, 2);
        ch_data->bs_num_env                 = num_rel_lead + 1;
        ch_data->t_env[ch_data->bs_num_env] = abs_bord_trail;

        for (i = 0; i < num_rel_lead; i++)
            ch_data->t_env[i + 1] = ch_data->t_env[i] + 2 * get_bits(gb, 2) + 2;

        bs_pointer = get_bits(gb, ceil_log2[ch_data->bs_num_env]);

        get_bits1_vector(gb, ch_data->bs_freq_res + 1, ch_data->bs_num_env);
        break;
    case VARVAR:
        ch_data->t_env[0]                   = get_bits(gb, 2);
        abs_bord_trail                     += get_bits(gb, 2);
        num_rel_lead                        = get_bits(gb, 2);
        num_rel_trail                       = get_bits(gb, 2);
        bs_num_env                          = num_rel_lead + num_rel_trail + 1;

        if (bs_num_env > 5) {
            av_log(ac->avctx, AV_LOG_ERROR,
                   "Invalid bitstream, too many SBR envelopes in VARVAR type SBR frame: %d\n",
                   bs_num_env);
            return -1;
        }
        ch_data->bs_num_env = bs_num_env;

        ch_data->t_env[ch_data->bs_num_env] = abs_bord_trail;

        for (i = 0; i < num_rel_lead; i++)
            ch_data->t_env[i + 1] = ch_data->t_env[i] + 2 * get_bits(gb, 2) + 2;
        for (i = 0; i < num_rel_trail; i++)
            ch_data->t_env[ch_data->bs_num_env - 1 - i] =
                ch_data->t_env[ch_data->bs_num_env - i] - 2 * get_bits(gb, 2) - 2;

        bs_pointer = get_bits(gb, ceil_log2[ch_data->bs_num_env]);

        get_bits1_vector(gb, ch_data->bs_freq_res + 1, ch_data->bs_num_env);
        break;
    }
    ch_data->bs_frame_class = bs_frame_class;

    av_assert0(bs_pointer >= 0);
    if (bs_pointer > ch_data->bs_num_env + 1) {
        av_log(ac->avctx, AV_LOG_ERROR,
               "Invalid bitstream, bs_pointer points to a middle noise border outside the time borders table: %d\n",
               bs_pointer);
        return -1;
    }

    for (i = 1; i <= ch_data->bs_num_env; i++) {
        if (ch_data->t_env[i-1] >= ch_data->t_env[i]) {
            av_log(ac->avctx, AV_LOG_ERROR, "Not strictly monotone time borders\n");
            return -1;
        }
    }

    ch_data->bs_num_noise = (ch_data->bs_num_env > 1) + 1;

    ch_data->t_q[0]                     = ch_data->t_env[0];
    ch_data->t_q[ch_data->bs_num_noise] = ch_data->t_env[ch_data->bs_num_env];
    if (ch_data->bs_num_noise > 1) {
        int idx;
        if (ch_data->bs_frame_class == FIXFIX) {
            idx = ch_data->bs_num_env >> 1;
        } else if (ch_data->bs_frame_class & 1) { // FIXVAR or VARVAR
            idx = ch_data->bs_num_env - FFMAX(bs_pointer - 1, 1);
        } else { // VARFIX
            if (!bs_pointer)
                idx = 1;
            else if (bs_pointer == 1)
                idx = ch_data->bs_num_env - 1;
            else // bs_pointer > 1
                idx = bs_pointer - 1;
        }
        ch_data->t_q[1] = ch_data->t_env[idx];
    }

    ch_data->e_a[0] = -(ch_data->e_a[1] != bs_num_env_old); // l_APrev
    ch_data->e_a[1] = -1;
    if ((ch_data->bs_frame_class & 1) && bs_pointer) { // FIXVAR or VARVAR and bs_pointer != 0
        ch_data->e_a[1] = ch_data->bs_num_env + 1 - bs_pointer;
    } else if ((ch_data->bs_frame_class == 2) && (bs_pointer > 1)) // VARFIX and bs_pointer > 1
        ch_data->e_a[1] = bs_pointer - 1;

    return 0;
}
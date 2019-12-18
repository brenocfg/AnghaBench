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
typedef  int int16_t ;
struct TYPE_6__ {int dc; } ;
typedef  TYPE_1__ Vp3Fragment ;
struct TYPE_7__ {int** num_coded_frags; int*** dct_tokens; int** coded_fragment_list; int /*<<< orphan*/  avctx; TYPE_1__* all_fragments; } ;
typedef  TYPE_2__ Vp3DecodeContext ;
struct TYPE_8__ {int /*<<< orphan*/  table; } ;
typedef  TYPE_3__ VLC ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int INT_MAX ; 
 int TOKEN_COEFF (int) ; 
 int TOKEN_EOB (int) ; 
 int TOKEN_ZERO_RUN (int,int) ; 
 int /*<<< orphan*/ * VLC_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ get_bits_left (int /*<<< orphan*/ *) ; 
 int get_coeff (int /*<<< orphan*/ *,int,int*) ; 
 int get_eob_run (int /*<<< orphan*/ *,int) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * vlc_table ; 

__attribute__((used)) static int unpack_vlcs(Vp3DecodeContext *s, GetBitContext *gb,
                       VLC *table, int coeff_index,
                       int plane,
                       int eob_run)
{
    int i, j = 0;
    int token;
    int zero_run  = 0;
    int16_t coeff = 0;
    int blocks_ended;
    int coeff_i = 0;
    int num_coeffs      = s->num_coded_frags[plane][coeff_index];
    int16_t *dct_tokens = s->dct_tokens[plane][coeff_index];

    /* local references to structure members to avoid repeated dereferences */
    int *coded_fragment_list   = s->coded_fragment_list[plane];
    Vp3Fragment *all_fragments = s->all_fragments;
    VLC_TYPE(*vlc_table)[2] = table->table;

    if (num_coeffs < 0) {
        av_log(s->avctx, AV_LOG_ERROR,
               "Invalid number of coefficients at level %d\n", coeff_index);
        return AVERROR_INVALIDDATA;
    }

    if (eob_run > num_coeffs) {
        coeff_i      =
        blocks_ended = num_coeffs;
        eob_run     -= num_coeffs;
    } else {
        coeff_i      =
        blocks_ended = eob_run;
        eob_run      = 0;
    }

    // insert fake EOB token to cover the split between planes or zzi
    if (blocks_ended)
        dct_tokens[j++] = blocks_ended << 2;

    while (coeff_i < num_coeffs && get_bits_left(gb) > 0) {
        /* decode a VLC into a token */
        token = get_vlc2(gb, vlc_table, 11, 3);
        /* use the token to get a zero run, a coefficient, and an eob run */
        if ((unsigned) token <= 6U) {
            eob_run = get_eob_run(gb, token);
            if (!eob_run)
                eob_run = INT_MAX;

            // record only the number of blocks ended in this plane,
            // any spill will be recorded in the next plane.
            if (eob_run > num_coeffs - coeff_i) {
                dct_tokens[j++] = TOKEN_EOB(num_coeffs - coeff_i);
                blocks_ended   += num_coeffs - coeff_i;
                eob_run        -= num_coeffs - coeff_i;
                coeff_i         = num_coeffs;
            } else {
                dct_tokens[j++] = TOKEN_EOB(eob_run);
                blocks_ended   += eob_run;
                coeff_i        += eob_run;
                eob_run         = 0;
            }
        } else if (token >= 0) {
            zero_run = get_coeff(gb, token, &coeff);

            if (zero_run) {
                dct_tokens[j++] = TOKEN_ZERO_RUN(coeff, zero_run);
            } else {
                // Save DC into the fragment structure. DC prediction is
                // done in raster order, so the actual DC can't be in with
                // other tokens. We still need the token in dct_tokens[]
                // however, or else the structure collapses on itself.
                if (!coeff_index)
                    all_fragments[coded_fragment_list[coeff_i]].dc = coeff;

                dct_tokens[j++] = TOKEN_COEFF(coeff);
            }

            if (coeff_index + zero_run > 64) {
                av_log(s->avctx, AV_LOG_DEBUG,
                       "Invalid zero run of %d with %d coeffs left\n",
                       zero_run, 64 - coeff_index);
                zero_run = 64 - coeff_index;
            }

            // zero runs code multiple coefficients,
            // so don't try to decode coeffs for those higher levels
            for (i = coeff_index + 1; i <= coeff_index + zero_run; i++)
                s->num_coded_frags[plane][i]--;
            coeff_i++;
        } else {
            av_log(s->avctx, AV_LOG_ERROR, "Invalid token %d\n", token);
            return -1;
        }
    }

    if (blocks_ended > s->num_coded_frags[plane][coeff_index])
        av_log(s->avctx, AV_LOG_ERROR, "More blocks ended than coded!\n");

    // decrement the number of blocks that have higher coefficients for each
    // EOB run at this level
    if (blocks_ended)
        for (i = coeff_index + 1; i < 64; i++)
            s->num_coded_frags[plane][i] -= blocks_ended;

    // setup the next buffer
    if (plane < 2)
        s->dct_tokens[plane + 1][coeff_index] = dct_tokens + j;
    else if (coeff_index < 63)
        s->dct_tokens[0][coeff_index + 1] = dct_tokens + j;

    return eob_run;
}
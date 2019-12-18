#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nsubbands; int limited_rate; int** quant_levels; int /*<<< orphan*/ ** grid_1_scf; int /*<<< orphan*/  gb; } ;
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ LBRChunk ;
typedef  TYPE_2__ DCALbrDecoder ;

/* Variables and functions */
 int DCA_LBR_SUBBANDS ; 
 size_t** ff_dca_sb_reorder ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ init_get_bits8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ parse_lpc (TYPE_2__*,int,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ parse_scale_factors (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ parse_ts (TYPE_2__*,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_high_res_grid(DCALbrDecoder *s, LBRChunk *chunk, int ch1, int ch2)
{
    int quant_levels[DCA_LBR_SUBBANDS];
    int sb, ch, ol, st, max_sb, profile;

    if (!chunk->len)
        return 0;

    if (init_get_bits8(&s->gb, chunk->data, chunk->len) < 0)
        return -1;

    // Quantizer profile
    profile = get_bits(&s->gb, 8);
    // Overall level
    ol = (profile >> 3) & 7;
    // Steepness
    st = profile >> 6;
    // Max energy subband
    max_sb = profile & 7;

    // Calculate quantization levels
    for (sb = 0; sb < s->nsubbands; sb++) {
        int f = sb * s->limited_rate / s->nsubbands;
        int a = 18000 / (12 * f / 1000 + 100 + 40 * st) + 20 * ol;
        if (a <= 95)
            quant_levels[sb] = 1;
        else if (a <= 140)
            quant_levels[sb] = 2;
        else if (a <= 180)
            quant_levels[sb] = 3;
        else if (a <= 230)
            quant_levels[sb] = 4;
        else
            quant_levels[sb] = 5;
    }

    // Reorder quantization levels for lower subbands
    for (sb = 0; sb < 8; sb++)
        s->quant_levels[ch1 / 2][sb] = quant_levels[ff_dca_sb_reorder[max_sb][sb]];
    for (; sb < s->nsubbands; sb++)
        s->quant_levels[ch1 / 2][sb] = quant_levels[sb];

    // LPC for the first two subbands
    if (parse_lpc(s, ch1, ch2, 0, 2) < 0)
        return -1;

    // Time-samples for the first two subbands of main channel
    if (parse_ts(s, ch1, ch2, 0, 2, 0) < 0)
        return -1;

    // First two bands of the first grid
    for (sb = 0; sb < 2; sb++)
        for (ch = ch1; ch <= ch2; ch++)
            if (parse_scale_factors(s, s->grid_1_scf[ch][sb]) < 0)
                return -1;

    return 0;
}
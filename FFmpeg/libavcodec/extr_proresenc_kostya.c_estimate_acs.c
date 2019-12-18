#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int const int16_t ;

/* Variables and functions */
 int const FFABS (int const) ; 
 size_t FFMIN (int,int) ; 
 scalar_t__ estimate_vlc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ff_prores_ac_codebook ; 
 int* ff_prores_lev_to_cb_index ; 
 int* ff_prores_run_to_cb_index ; 

__attribute__((used)) static int estimate_acs(int *error, int16_t *blocks, int blocks_per_slice,
                        int plane_size_factor,
                        const uint8_t *scan, const int16_t *qmat)
{
    int idx, i;
    int run, level, run_cb, lev_cb;
    int max_coeffs, abs_level;
    int bits = 0;

    max_coeffs = blocks_per_slice << 6;
    run_cb     = ff_prores_run_to_cb_index[4];
    lev_cb     = ff_prores_lev_to_cb_index[2];
    run        = 0;

    for (i = 1; i < 64; i++) {
        for (idx = scan[i]; idx < max_coeffs; idx += 64) {
            level   = blocks[idx] / qmat[scan[i]];
            *error += FFABS(blocks[idx]) % qmat[scan[i]];
            if (level) {
                abs_level = FFABS(level);
                bits += estimate_vlc(ff_prores_ac_codebook[run_cb], run);
                bits += estimate_vlc(ff_prores_ac_codebook[lev_cb],
                                     abs_level - 1) + 1;

                run_cb = ff_prores_run_to_cb_index[FFMIN(run, 15)];
                lev_cb = ff_prores_lev_to_cb_index[FFMIN(abs_level, 9)];
                run    = 0;
            } else {
                run++;
            }
        }
    }

    return bits;
}
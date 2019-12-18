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
typedef  int /*<<< orphan*/  NellyMoserEncodeContext ;

/* Variables and functions */
 int NELLY_BANDS ; 
 int* ff_nelly_delta_table ; 
 int* ff_nelly_init_table ; 
 int /*<<< orphan*/  find_best (float,int*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sf_delta_lut ; 
 int /*<<< orphan*/  sf_lut ; 

__attribute__((used)) static void get_exponent_greedy(NellyMoserEncodeContext *s, float *cand, int *idx_table)
{
    int band, best_idx, power_idx = 0;
    float power_candidate;

    //base exponent
    find_best(cand[0], ff_nelly_init_table, sf_lut, -20, 96);
    idx_table[0] = best_idx;
    power_idx = ff_nelly_init_table[best_idx];

    for (band = 1; band < NELLY_BANDS; band++) {
        power_candidate = cand[band] - power_idx;
        find_best(power_candidate, ff_nelly_delta_table, sf_delta_lut, 37, 78);
        idx_table[band] = best_idx;
        power_idx += ff_nelly_delta_table[best_idx];
    }
}
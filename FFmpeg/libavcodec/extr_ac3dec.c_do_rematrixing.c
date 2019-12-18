#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* end_freq; int num_rematrixing_bands; int** fixed_coeffs; scalar_t__* rematrixing_flags; } ;
typedef  TYPE_1__ AC3DecodeContext ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int* ff_ac3_rematrix_band_tab ; 

__attribute__((used)) static void do_rematrixing(AC3DecodeContext *s)
{
    int bnd, i;
    int end, bndend;

    end = FFMIN(s->end_freq[1], s->end_freq[2]);

    for (bnd = 0; bnd < s->num_rematrixing_bands; bnd++) {
        if (s->rematrixing_flags[bnd]) {
            bndend = FFMIN(end, ff_ac3_rematrix_band_tab[bnd + 1]);
            for (i = ff_ac3_rematrix_band_tab[bnd]; i < bndend; i++) {
                int tmp0 = s->fixed_coeffs[1][i];
                s->fixed_coeffs[1][i] += s->fixed_coeffs[2][i];
                s->fixed_coeffs[2][i]  = tmp0 - s->fixed_coeffs[2][i];
            }
        }
    }
}
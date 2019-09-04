#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nsubbands; int min_mono_subband; int /*<<< orphan*/  gb; scalar_t__** grid_3_avg; int /*<<< orphan*/ ** grid_1_scf; } ;
typedef  TYPE_1__ DCALbrDecoder ;

/* Variables and functions */
 scalar_t__ ensure_bits (int /*<<< orphan*/ *,int) ; 
 int* ff_dca_grid_1_to_scf ; 
 int* ff_dca_scf_to_grid_1 ; 
 int /*<<< orphan*/  ff_dca_vlc_avg_g3 ; 
 scalar_t__ parse_scale_factors (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ parse_vlc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int parse_grid_1_sec_ch(DCALbrDecoder *s, int ch2)
{
    int sb, nsubbands;

    // Scale factors
    nsubbands = ff_dca_scf_to_grid_1[s->nsubbands - 1] + 1;
    for (sb = 2; sb < nsubbands; sb++) {
        if (ff_dca_grid_1_to_scf[sb] >= s->min_mono_subband
            && parse_scale_factors(s, s->grid_1_scf[ch2][sb]) < 0)
            return -1;
    }

    // Average values for third grid
    for (sb = 0; sb < s->nsubbands - 4; sb++) {
        if (sb + 4 >= s->min_mono_subband) {
            if (ensure_bits(&s->gb, 20))
                return 0;
            s->grid_3_avg[ch2][sb] = parse_vlc(&s->gb, &ff_dca_vlc_avg_g3, 2) - 16;
        }
    }

    return 0;
}
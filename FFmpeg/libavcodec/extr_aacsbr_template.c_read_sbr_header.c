#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
struct TYPE_7__ {int bs_freq_scale; int bs_alter_scale; int bs_noise_bands; void* bs_xover_band; void* bs_stop_freq; void* bs_start_freq; } ;
struct TYPE_6__ {int bs_limiter_bands; int start; int reset; int bs_limiter_gains; int bs_interpol_freq; int bs_smoothing_mode; TYPE_4__ spectrum_params; void* bs_amp_res_header; scalar_t__ ready_for_dequant; } ;
typedef  int /*<<< orphan*/  SpectrumParameters ;
typedef  TYPE_1__ SpectralBandReplication ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 
 unsigned int get_bits_count (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  sbr_make_f_tablelim (TYPE_1__*) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static unsigned int read_sbr_header(SpectralBandReplication *sbr, GetBitContext *gb)
{
    unsigned int cnt = get_bits_count(gb);
    uint8_t bs_header_extra_1;
    uint8_t bs_header_extra_2;
    int old_bs_limiter_bands = sbr->bs_limiter_bands;
    SpectrumParameters old_spectrum_params;

    sbr->start = 1;
    sbr->ready_for_dequant = 0;

    // Save last spectrum parameters variables to compare to new ones
    memcpy(&old_spectrum_params, &sbr->spectrum_params, sizeof(SpectrumParameters));

    sbr->bs_amp_res_header              = get_bits1(gb);
    sbr->spectrum_params.bs_start_freq  = get_bits(gb, 4);
    sbr->spectrum_params.bs_stop_freq   = get_bits(gb, 4);
    sbr->spectrum_params.bs_xover_band  = get_bits(gb, 3);
                                          skip_bits(gb, 2); // bs_reserved

    bs_header_extra_1 = get_bits1(gb);
    bs_header_extra_2 = get_bits1(gb);

    if (bs_header_extra_1) {
        sbr->spectrum_params.bs_freq_scale  = get_bits(gb, 2);
        sbr->spectrum_params.bs_alter_scale = get_bits1(gb);
        sbr->spectrum_params.bs_noise_bands = get_bits(gb, 2);
    } else {
        sbr->spectrum_params.bs_freq_scale  = 2;
        sbr->spectrum_params.bs_alter_scale = 1;
        sbr->spectrum_params.bs_noise_bands = 2;
    }

    // Check if spectrum parameters changed
    if (memcmp(&old_spectrum_params, &sbr->spectrum_params, sizeof(SpectrumParameters)))
        sbr->reset = 1;

    if (bs_header_extra_2) {
        sbr->bs_limiter_bands  = get_bits(gb, 2);
        sbr->bs_limiter_gains  = get_bits(gb, 2);
        sbr->bs_interpol_freq  = get_bits1(gb);
        sbr->bs_smoothing_mode = get_bits1(gb);
    } else {
        sbr->bs_limiter_bands  = 2;
        sbr->bs_limiter_gains  = 2;
        sbr->bs_interpol_freq  = 1;
        sbr->bs_smoothing_mode = 1;
    }

    if (sbr->bs_limiter_bands != old_bs_limiter_bands && !sbr->reset)
        sbr_make_f_tablelim(sbr);

    return get_bits_count(gb) - cnt;
}
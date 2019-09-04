#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  bs_add_harmonic; void* bs_add_harmonic_flag; int /*<<< orphan*/ * bs_invf_mode; } ;
struct TYPE_15__ {int /*<<< orphan*/ * n; TYPE_3__* data; void* bs_coupling; } ;
typedef  TYPE_1__ SpectralBandReplication ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  int /*<<< orphan*/  AACContext ;

/* Variables and functions */
 int /*<<< orphan*/  copy_sbr_grid (TYPE_3__*,TYPE_3__*) ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_bits1_vector (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_sbr_dtdf (TYPE_1__*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int read_sbr_envelope (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 scalar_t__ read_sbr_grid (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  read_sbr_invf (TYPE_1__*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int read_sbr_noise (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int read_sbr_channel_pair_element(AACContext *ac,
                                          SpectralBandReplication *sbr,
                                          GetBitContext *gb)
{
    int ret;

    if (get_bits1(gb))    // bs_data_extra
        skip_bits(gb, 8); // bs_reserved

    if ((sbr->bs_coupling = get_bits1(gb))) {
        if (read_sbr_grid(ac, sbr, gb, &sbr->data[0]))
            return -1;
        copy_sbr_grid(&sbr->data[1], &sbr->data[0]);
        read_sbr_dtdf(sbr, gb, &sbr->data[0]);
        read_sbr_dtdf(sbr, gb, &sbr->data[1]);
        read_sbr_invf(sbr, gb, &sbr->data[0]);
        memcpy(sbr->data[1].bs_invf_mode[1], sbr->data[1].bs_invf_mode[0], sizeof(sbr->data[1].bs_invf_mode[0]));
        memcpy(sbr->data[1].bs_invf_mode[0], sbr->data[0].bs_invf_mode[0], sizeof(sbr->data[1].bs_invf_mode[0]));
        if((ret = read_sbr_envelope(ac, sbr, gb, &sbr->data[0], 0)) < 0)
            return ret;
        if((ret = read_sbr_noise(ac, sbr, gb, &sbr->data[0], 0)) < 0)
            return ret;
        if((ret = read_sbr_envelope(ac, sbr, gb, &sbr->data[1], 1)) < 0)
            return ret;
        if((ret = read_sbr_noise(ac, sbr, gb, &sbr->data[1], 1)) < 0)
            return ret;
    } else {
        if (read_sbr_grid(ac, sbr, gb, &sbr->data[0]) ||
            read_sbr_grid(ac, sbr, gb, &sbr->data[1]))
            return -1;
        read_sbr_dtdf(sbr, gb, &sbr->data[0]);
        read_sbr_dtdf(sbr, gb, &sbr->data[1]);
        read_sbr_invf(sbr, gb, &sbr->data[0]);
        read_sbr_invf(sbr, gb, &sbr->data[1]);
        if((ret = read_sbr_envelope(ac, sbr, gb, &sbr->data[0], 0)) < 0)
            return ret;
        if((ret = read_sbr_envelope(ac, sbr, gb, &sbr->data[1], 1)) < 0)
            return ret;
        if((ret = read_sbr_noise(ac, sbr, gb, &sbr->data[0], 0)) < 0)
            return ret;
        if((ret = read_sbr_noise(ac, sbr, gb, &sbr->data[1], 1)) < 0)
            return ret;
    }

    if ((sbr->data[0].bs_add_harmonic_flag = get_bits1(gb)))
        get_bits1_vector(gb, sbr->data[0].bs_add_harmonic, sbr->n[1]);
    if ((sbr->data[1].bs_add_harmonic_flag = get_bits1(gb)))
        get_bits1_vector(gb, sbr->data[1].bs_add_harmonic, sbr->n[1]);

    return 0;
}
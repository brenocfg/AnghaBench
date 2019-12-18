#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  bs_add_harmonic; scalar_t__ bs_add_harmonic_flag; } ;
struct TYPE_13__ {int /*<<< orphan*/ * n; TYPE_4__* data; } ;
typedef  TYPE_1__ SpectralBandReplication ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  int /*<<< orphan*/  AACContext ;

/* Variables and functions */
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_bits1_vector (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_sbr_dtdf (TYPE_1__*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int read_sbr_envelope (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ read_sbr_grid (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  read_sbr_invf (TYPE_1__*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int read_sbr_noise (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int read_sbr_single_channel_element(AACContext *ac,
                                            SpectralBandReplication *sbr,
                                            GetBitContext *gb)
{
    int ret;

    if (get_bits1(gb)) // bs_data_extra
        skip_bits(gb, 4); // bs_reserved

    if (read_sbr_grid(ac, sbr, gb, &sbr->data[0]))
        return -1;
    read_sbr_dtdf(sbr, gb, &sbr->data[0]);
    read_sbr_invf(sbr, gb, &sbr->data[0]);
    if((ret = read_sbr_envelope(ac, sbr, gb, &sbr->data[0], 0)) < 0)
        return ret;
    if((ret = read_sbr_noise(ac, sbr, gb, &sbr->data[0], 0)) < 0)
        return ret;

    if ((sbr->data[0].bs_add_harmonic_flag = get_bits1(gb)))
        get_bits1_vector(gb, sbr->data[0].bs_add_harmonic, sbr->n[1]);

    return 0;
}
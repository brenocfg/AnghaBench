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
struct TYPE_4__ {int /*<<< orphan*/  numTemporalLayers; } ;
typedef  TYPE_1__ HEVCDecoderConfigurationRecord ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  FFMAX (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hvcc_parse_ptl (int /*<<< orphan*/ *,TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int hvcc_parse_vps(GetBitContext *gb,
                          HEVCDecoderConfigurationRecord *hvcc)
{
    unsigned int vps_max_sub_layers_minus1;

    /*
     * vps_video_parameter_set_id u(4)
     * vps_reserved_three_2bits   u(2)
     * vps_max_layers_minus1      u(6)
     */
    skip_bits(gb, 12);

    vps_max_sub_layers_minus1 = get_bits(gb, 3);

    /*
     * numTemporalLayers greater than 1 indicates that the stream to which this
     * configuration record applies is temporally scalable and the contained
     * number of temporal layers (also referred to as temporal sub-layer or
     * sub-layer in ISO/IEC 23008-2) is equal to numTemporalLayers. Value 1
     * indicates that the stream is not temporally scalable. Value 0 indicates
     * that it is unknown whether the stream is temporally scalable.
     */
    hvcc->numTemporalLayers = FFMAX(hvcc->numTemporalLayers,
                                    vps_max_sub_layers_minus1 + 1);

    /*
     * vps_temporal_id_nesting_flag u(1)
     * vps_reserved_0xffff_16bits   u(16)
     */
    skip_bits(gb, 17);

    hvcc_parse_ptl(gb, hvcc, vps_max_sub_layers_minus1);

    /* nothing useful for hvcC past this point */
    return 0;
}
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
typedef  void* uint8_t ;
struct TYPE_3__ {void* level_idc; int /*<<< orphan*/  constraint_indicator_flags; int /*<<< orphan*/  profile_compatibility_flags; void* profile_idc; void* tier_flag; void* profile_space; } ;
typedef  TYPE_1__ HVCCProfileTierLevel ;
typedef  int /*<<< orphan*/  HEVCDecoderConfigurationRecord ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int HEVC_MAX_SUB_LAYERS ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_bits64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_bits_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hvcc_update_ptl (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits_long (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void hvcc_parse_ptl(GetBitContext *gb,
                           HEVCDecoderConfigurationRecord *hvcc,
                           unsigned int max_sub_layers_minus1)
{
    unsigned int i;
    HVCCProfileTierLevel general_ptl;
    uint8_t sub_layer_profile_present_flag[HEVC_MAX_SUB_LAYERS];
    uint8_t sub_layer_level_present_flag[HEVC_MAX_SUB_LAYERS];

    general_ptl.profile_space               = get_bits(gb, 2);
    general_ptl.tier_flag                   = get_bits1(gb);
    general_ptl.profile_idc                 = get_bits(gb, 5);
    general_ptl.profile_compatibility_flags = get_bits_long(gb, 32);
    general_ptl.constraint_indicator_flags  = get_bits64(gb, 48);
    general_ptl.level_idc                   = get_bits(gb, 8);
    hvcc_update_ptl(hvcc, &general_ptl);

    for (i = 0; i < max_sub_layers_minus1; i++) {
        sub_layer_profile_present_flag[i] = get_bits1(gb);
        sub_layer_level_present_flag[i]   = get_bits1(gb);
    }

    if (max_sub_layers_minus1 > 0)
        for (i = max_sub_layers_minus1; i < 8; i++)
            skip_bits(gb, 2); // reserved_zero_2bits[i]

    for (i = 0; i < max_sub_layers_minus1; i++) {
        if (sub_layer_profile_present_flag[i]) {
            /*
             * sub_layer_profile_space[i]                     u(2)
             * sub_layer_tier_flag[i]                         u(1)
             * sub_layer_profile_idc[i]                       u(5)
             * sub_layer_profile_compatibility_flag[i][0..31] u(32)
             * sub_layer_progressive_source_flag[i]           u(1)
             * sub_layer_interlaced_source_flag[i]            u(1)
             * sub_layer_non_packed_constraint_flag[i]        u(1)
             * sub_layer_frame_only_constraint_flag[i]        u(1)
             * sub_layer_reserved_zero_44bits[i]              u(44)
             */
            skip_bits_long(gb, 32);
            skip_bits_long(gb, 32);
            skip_bits     (gb, 24);
        }

        if (sub_layer_level_present_flag[i])
            skip_bits(gb, 8);
    }
}
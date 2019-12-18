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
struct TYPE_3__ {scalar_t__ profile; int bitdepth; int monochrome; int color_description_present_flag; int chroma_subsampling_x; int chroma_subsampling_y; void* chroma_sample_position; void* color_range; void* matrix_coefficients; void* transfer_characteristics; void* color_primaries; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ AV1SequenceParameters ;

/* Variables and functions */
 void* AVCOL_PRI_BT709 ; 
 void* AVCOL_PRI_UNSPECIFIED ; 
 void* AVCOL_SPC_RGB ; 
 void* AVCOL_SPC_UNSPECIFIED ; 
 void* AVCOL_TRC_IEC61966_2_1 ; 
 void* AVCOL_TRC_UNSPECIFIED ; 
 scalar_t__ FF_PROFILE_AV1_HIGH ; 
 scalar_t__ FF_PROFILE_AV1_MAIN ; 
 scalar_t__ FF_PROFILE_AV1_PROFESSIONAL ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_color_config(AV1SequenceParameters *seq_params, GetBitContext *gb)
{
    int twelve_bit = 0;
    int high_bitdepth = get_bits1(gb);
    if (seq_params->profile == FF_PROFILE_AV1_PROFESSIONAL && high_bitdepth)
        twelve_bit = get_bits1(gb);

    seq_params->bitdepth = 8 + (high_bitdepth * 2) + (twelve_bit * 2);

    if (seq_params->profile == FF_PROFILE_AV1_HIGH)
        seq_params->monochrome = 0;
    else
        seq_params->monochrome = get_bits1(gb);

    seq_params->color_description_present_flag = get_bits1(gb);
    if (seq_params->color_description_present_flag) {
        seq_params->color_primaries          = get_bits(gb, 8);
        seq_params->transfer_characteristics = get_bits(gb, 8);
        seq_params->matrix_coefficients      = get_bits(gb, 8);
    } else {
        seq_params->color_primaries          = AVCOL_PRI_UNSPECIFIED;
        seq_params->transfer_characteristics = AVCOL_TRC_UNSPECIFIED;
        seq_params->matrix_coefficients      = AVCOL_SPC_UNSPECIFIED;
    }

    if (seq_params->monochrome) {
        seq_params->color_range = get_bits1(gb);
        seq_params->chroma_subsampling_x = 1;
        seq_params->chroma_subsampling_y = 1;
        seq_params->chroma_sample_position = 0;
        return 0;
    } else if (seq_params->color_primaries          == AVCOL_PRI_BT709 &&
               seq_params->transfer_characteristics == AVCOL_TRC_IEC61966_2_1 &&
               seq_params->matrix_coefficients      == AVCOL_SPC_RGB) {
        seq_params->chroma_subsampling_x = 0;
        seq_params->chroma_subsampling_y = 0;
    } else {
        seq_params->color_range = get_bits1(gb);

        if (seq_params->profile == FF_PROFILE_AV1_MAIN) {
            seq_params->chroma_subsampling_x = 1;
            seq_params->chroma_subsampling_y = 1;
        } else if (seq_params->profile == FF_PROFILE_AV1_HIGH) {
            seq_params->chroma_subsampling_x = 0;
            seq_params->chroma_subsampling_y = 0;
        } else {
            if (twelve_bit) {
                seq_params->chroma_subsampling_x = get_bits1(gb);
                if (seq_params->chroma_subsampling_x)
                    seq_params->chroma_subsampling_y = get_bits1(gb);
                else
                    seq_params->chroma_subsampling_y = 0;
            } else {
                seq_params->chroma_subsampling_x = 1;
                seq_params->chroma_subsampling_y = 0;
            }
        }
        if (seq_params->chroma_subsampling_x && seq_params->chroma_subsampling_y)
            seq_params->chroma_sample_position = get_bits(gb, 2);
    }

    skip_bits1(gb); // separate_uv_delta_q

    return 0;
}
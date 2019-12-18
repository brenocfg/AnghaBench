#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int num; int den; } ;
struct TYPE_6__ {int profile_idc; int constraint_set_flags; int id; int chroma_format_idc; int bit_depth_luma; int frame_mbs_only_flag; TYPE_3__ sar; void* level_idc; } ;
typedef  TYPE_1__ H264SequenceParameterSet ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (TYPE_3__*) ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* av_mallocz (int) ; 
 TYPE_3__* avc_sample_aspect_ratio ; 
 int /*<<< orphan*/ * ff_nal_unit_extract_rbsp (int /*<<< orphan*/  const*,int,int*,int /*<<< orphan*/ ) ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int get_se_golomb (int /*<<< orphan*/ *) ; 
 int get_ue_golomb (int /*<<< orphan*/ *) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits1 (int /*<<< orphan*/ *) ; 

H264SequenceParameterSet *ff_avc_decode_sps(const uint8_t *buf, int buf_size)
{
    int i, j, ret, rbsp_size, aspect_ratio_idc, pic_order_cnt_type;
    int num_ref_frames_in_pic_order_cnt_cycle;
    int delta_scale, lastScale = 8, nextScale = 8;
    int sizeOfScalingList;
    H264SequenceParameterSet *sps = NULL;
    GetBitContext gb;
    uint8_t *rbsp_buf;

    rbsp_buf = ff_nal_unit_extract_rbsp(buf, buf_size, &rbsp_size, 0);
    if (!rbsp_buf)
        return NULL;

    ret = init_get_bits8(&gb, rbsp_buf, rbsp_size);
    if (ret < 0)
        goto end;

    sps = av_mallocz(sizeof(*sps));
    if (!sps)
        goto end;

    sps->profile_idc = get_bits(&gb, 8);
    sps->constraint_set_flags |= get_bits1(&gb) << 0; // constraint_set0_flag
    sps->constraint_set_flags |= get_bits1(&gb) << 1; // constraint_set1_flag
    sps->constraint_set_flags |= get_bits1(&gb) << 2; // constraint_set2_flag
    sps->constraint_set_flags |= get_bits1(&gb) << 3; // constraint_set3_flag
    sps->constraint_set_flags |= get_bits1(&gb) << 4; // constraint_set4_flag
    sps->constraint_set_flags |= get_bits1(&gb) << 5; // constraint_set5_flag
    skip_bits(&gb, 2); // reserved_zero_2bits
    sps->level_idc = get_bits(&gb, 8);
    sps->id = get_ue_golomb(&gb);

    if (sps->profile_idc == 100 || sps->profile_idc == 110 ||
        sps->profile_idc == 122 || sps->profile_idc == 244 || sps->profile_idc ==  44 ||
        sps->profile_idc ==  83 || sps->profile_idc ==  86 || sps->profile_idc == 118 ||
        sps->profile_idc == 128 || sps->profile_idc == 138 || sps->profile_idc == 139 ||
        sps->profile_idc == 134) {
        sps->chroma_format_idc = get_ue_golomb(&gb); // chroma_format_idc
        if (sps->chroma_format_idc == 3) {
            skip_bits1(&gb); // separate_colour_plane_flag
        }
        sps->bit_depth_luma = get_ue_golomb(&gb) + 8;
        get_ue_golomb(&gb); // bit_depth_chroma_minus8
        skip_bits1(&gb); // qpprime_y_zero_transform_bypass_flag
        if (get_bits1(&gb)) { // seq_scaling_matrix_present_flag
            for (i = 0; i < ((sps->chroma_format_idc != 3) ? 8 : 12); i++) {
                if (!get_bits1(&gb)) // seq_scaling_list_present_flag
                    continue;
                lastScale = 8;
                nextScale = 8;
                sizeOfScalingList = i < 6 ? 16 : 64;
                for (j = 0; j < sizeOfScalingList; j++) {
                    if (nextScale != 0) {
                        delta_scale = get_se_golomb(&gb);
                        nextScale = (lastScale + delta_scale) & 0xff;
                    }
                    lastScale = nextScale == 0 ? lastScale : nextScale;
                }
            }
        }
    } else {
        sps->chroma_format_idc = 1;
        sps->bit_depth_luma = 8;
    }

    get_ue_golomb(&gb); // log2_max_frame_num_minus4
    pic_order_cnt_type = get_ue_golomb(&gb);

    if (pic_order_cnt_type == 0) {
        get_ue_golomb(&gb); // log2_max_pic_order_cnt_lsb_minus4
    } else if (pic_order_cnt_type == 1) {
        skip_bits1(&gb);    // delta_pic_order_always_zero
        get_se_golomb(&gb); // offset_for_non_ref_pic
        get_se_golomb(&gb); // offset_for_top_to_bottom_field
        num_ref_frames_in_pic_order_cnt_cycle = get_ue_golomb(&gb);
        for (i = 0; i < num_ref_frames_in_pic_order_cnt_cycle; i++)
            get_se_golomb(&gb); // offset_for_ref_frame
    }

    get_ue_golomb(&gb); // max_num_ref_frames
    skip_bits1(&gb); // gaps_in_frame_num_value_allowed_flag
    get_ue_golomb(&gb); // pic_width_in_mbs_minus1
    get_ue_golomb(&gb); // pic_height_in_map_units_minus1

    sps->frame_mbs_only_flag = get_bits1(&gb);
    if (!sps->frame_mbs_only_flag)
        skip_bits1(&gb); // mb_adaptive_frame_field_flag

    skip_bits1(&gb); // direct_8x8_inference_flag

    if (get_bits1(&gb)) { // frame_cropping_flag
        get_ue_golomb(&gb); // frame_crop_left_offset
        get_ue_golomb(&gb); // frame_crop_right_offset
        get_ue_golomb(&gb); // frame_crop_top_offset
        get_ue_golomb(&gb); // frame_crop_bottom_offset
    }

    if (get_bits1(&gb)) { // vui_parameters_present_flag
        if (get_bits1(&gb)) { // aspect_ratio_info_present_flag
            aspect_ratio_idc = get_bits(&gb, 8);
            if (aspect_ratio_idc == 0xff) {
                sps->sar.num = get_bits(&gb, 16);
                sps->sar.den = get_bits(&gb, 16);
            } else if (aspect_ratio_idc < FF_ARRAY_ELEMS(avc_sample_aspect_ratio)) {
                sps->sar = avc_sample_aspect_ratio[aspect_ratio_idc];
            }
        }
    }

    if (!sps->sar.den) {
        sps->sar.num = 1;
        sps->sar.den = 1;
    }

 end:
    av_free(rbsp_buf);
    return sps;
}
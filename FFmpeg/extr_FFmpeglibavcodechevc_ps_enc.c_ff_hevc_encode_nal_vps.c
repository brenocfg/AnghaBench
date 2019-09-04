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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int vps_max_layers; int vps_max_sub_layers; int vps_temporal_id_nesting_flag; int vps_sub_layer_ordering_info_present_flag; int* vps_max_dec_pic_buffering; int* vps_num_reorder_pics; int* vps_max_latency_increase; int vps_max_layer_id; int vps_num_layer_sets; int vps_timing_info_present_flag; int vps_poc_proportional_to_timing_flag; int vps_num_ticks_poc_diff_one; int vps_num_hrd_parameters; int /*<<< orphan*/  vps_time_scale; int /*<<< orphan*/  vps_num_units_in_tick; int /*<<< orphan*/  ptl; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_1__ HEVCVPS ;

/* Variables and functions */
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  avpriv_align_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_report_missing_feature (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  flush_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_put_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  put_bits32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int put_bits_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_ue_golomb (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  write_ptl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int ff_hevc_encode_nal_vps(HEVCVPS *vps, unsigned int id,
                           uint8_t *buf, int buf_size)
{
    PutBitContext pb;
    int i, data_size;

    init_put_bits(&pb, buf, buf_size);
    put_bits(&pb,  4, id);
    put_bits(&pb,  2, 3);                               // reserved
    put_bits(&pb,  6, vps->vps_max_layers - 1);
    put_bits(&pb,  3, vps->vps_max_sub_layers - 1);
    put_bits(&pb,  1, vps->vps_temporal_id_nesting_flag);
    put_bits(&pb, 16, 0xffff);                          // reserved

    write_ptl(&pb, &vps->ptl, vps->vps_max_sub_layers);

    put_bits(&pb, 1, vps->vps_sub_layer_ordering_info_present_flag);
    for (i = vps->vps_sub_layer_ordering_info_present_flag ? 0 : vps->vps_max_layers - 1;
         i < vps->vps_max_sub_layers; i++) {
        set_ue_golomb(&pb, vps->vps_max_dec_pic_buffering[i] - 1);
        set_ue_golomb(&pb, vps->vps_num_reorder_pics[i]);
        set_ue_golomb(&pb, vps->vps_max_latency_increase[i] + 1);
    }

    put_bits(&pb, 6, vps->vps_max_layer_id);
    set_ue_golomb(&pb, vps->vps_num_layer_sets - 1);

    if (vps->vps_num_layer_sets > 1) {
        avpriv_report_missing_feature(NULL, "Writing layer_id_included_flag");
        return AVERROR_PATCHWELCOME;
    }

    put_bits(&pb, 1, vps->vps_timing_info_present_flag);
    if (vps->vps_timing_info_present_flag) {
        put_bits32(&pb, vps->vps_num_units_in_tick);
        put_bits32(&pb, vps->vps_time_scale);
        put_bits(&pb, 1, vps->vps_poc_proportional_to_timing_flag);
        if (vps->vps_poc_proportional_to_timing_flag)
            set_ue_golomb(&pb, vps->vps_num_ticks_poc_diff_one - 1);

        set_ue_golomb(&pb, vps->vps_num_hrd_parameters);
        if (vps->vps_num_hrd_parameters) {
            avpriv_report_missing_feature(NULL, "Writing HRD parameters");
            return AVERROR_PATCHWELCOME;
        }
    }

    put_bits(&pb, 1, 0);    // extension flag

    put_bits(&pb, 1, 1);    // stop bit
    avpriv_align_put_bits(&pb);

    data_size = put_bits_count(&pb) / 8;
    flush_put_bits(&pb);

    return data_size;
}
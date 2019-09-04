#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__** sps_list; } ;
struct TYPE_9__ {int present; void** initial_cpb_removal_delay; } ;
struct TYPE_8__ {int cpb_cnt; int /*<<< orphan*/  initial_cpb_removal_delay_length; scalar_t__ vcl_hrd_parameters_present_flag; scalar_t__ nal_hrd_parameters_present_flag; } ;
struct TYPE_7__ {scalar_t__ data; } ;
typedef  TYPE_2__ SPS ;
typedef  TYPE_3__ H264SEIBufferingPeriod ;
typedef  TYPE_4__ H264ParamSets ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PS_NOT_FOUND ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 void* get_bits_long (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int get_ue_golomb_31 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_buffering_period(H264SEIBufferingPeriod *h, GetBitContext *gb,
                                   const H264ParamSets *ps, void *logctx)
{
    unsigned int sps_id;
    int sched_sel_idx;
    const SPS *sps;

    sps_id = get_ue_golomb_31(gb);
    if (sps_id > 31 || !ps->sps_list[sps_id]) {
        av_log(logctx, AV_LOG_ERROR,
               "non-existing SPS %d referenced in buffering period\n", sps_id);
        return sps_id > 31 ? AVERROR_INVALIDDATA : AVERROR_PS_NOT_FOUND;
    }
    sps = (const SPS*)ps->sps_list[sps_id]->data;

    // NOTE: This is really so duplicated in the standard... See H.264, D.1.1
    if (sps->nal_hrd_parameters_present_flag) {
        for (sched_sel_idx = 0; sched_sel_idx < sps->cpb_cnt; sched_sel_idx++) {
            h->initial_cpb_removal_delay[sched_sel_idx] =
                get_bits_long(gb, sps->initial_cpb_removal_delay_length);
            // initial_cpb_removal_delay_offset
            skip_bits(gb, sps->initial_cpb_removal_delay_length);
        }
    }
    if (sps->vcl_hrd_parameters_present_flag) {
        for (sched_sel_idx = 0; sched_sel_idx < sps->cpb_cnt; sched_sel_idx++) {
            h->initial_cpb_removal_delay[sched_sel_idx] =
                get_bits_long(gb, sps->initial_cpb_removal_delay_length);
            // initial_cpb_removal_delay_offset
            skip_bits(gb, sps->initial_cpb_removal_delay_length);
        }
    }

    h->present = 1;
    return 0;
}
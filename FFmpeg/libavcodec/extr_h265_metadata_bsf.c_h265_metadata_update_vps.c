#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_4__* priv_data; } ;
struct TYPE_9__ {scalar_t__ den; scalar_t__ num; } ;
struct TYPE_12__ {scalar_t__ num_ticks_poc_diff_one; TYPE_1__ tick_rate; } ;
struct TYPE_10__ {int /*<<< orphan*/  general_level_idc; } ;
struct TYPE_11__ {int vps_time_scale; int vps_num_units_in_tick; int vps_timing_info_present_flag; scalar_t__ vps_num_ticks_poc_diff_one_minus1; int vps_poc_proportional_to_timing_flag; TYPE_2__ profile_tier_level; } ;
typedef  TYPE_3__ H265RawVPS ;
typedef  TYPE_4__ H265MetadataContext ;
typedef  TYPE_5__ AVBSFContext ;

/* Variables and functions */
 scalar_t__ INT_MAX ; 
 scalar_t__ UINT32_MAX ; 
 int /*<<< orphan*/  av_reduce (int*,int*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  h265_metadata_update_level (TYPE_5__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int h265_metadata_update_vps(AVBSFContext *bsf,
                                    H265RawVPS *vps)
{
    H265MetadataContext *ctx = bsf->priv_data;

    if (ctx->tick_rate.num && ctx->tick_rate.den) {
        int num, den;

        av_reduce(&num, &den, ctx->tick_rate.num, ctx->tick_rate.den,
                  UINT32_MAX > INT_MAX ? UINT32_MAX : INT_MAX);

        vps->vps_time_scale        = num;
        vps->vps_num_units_in_tick = den;

        vps->vps_timing_info_present_flag = 1;

        if (ctx->num_ticks_poc_diff_one > 0) {
            vps->vps_num_ticks_poc_diff_one_minus1 =
                ctx->num_ticks_poc_diff_one - 1;
            vps->vps_poc_proportional_to_timing_flag = 1;
        } else if (ctx->num_ticks_poc_diff_one == 0) {
            vps->vps_poc_proportional_to_timing_flag = 0;
        }
    }

    h265_metadata_update_level(bsf, &vps->profile_tier_level.general_level_idc);

    return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_13__ {int max_br_high; int max_luma_ps; int max_slice_segments_per_picture; int max_tile_rows; int max_tile_cols; int max_br_main; } ;
struct TYPE_12__ {scalar_t__ lower_bit_rate; int profile_idc; int max_dpb_pic_buf; scalar_t__ cpb_nal_factor; scalar_t__ intra; scalar_t__ high_throughput; } ;
struct TYPE_11__ {int general_tier_flag; int general_lower_bit_rate_constraint_flag; } ;
typedef  TYPE_1__ H265RawProfileTierLevel ;
typedef  TYPE_2__ H265ProfileDescriptor ;
typedef  TYPE_3__ H265LevelDescriptor ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int FF_ARRAY_ELEMS (TYPE_3__*) ; 
 TYPE_2__* ff_h265_get_profile (TYPE_1__ const*) ; 
 TYPE_3__* h265_levels ; 
 TYPE_2__* h265_profiles ; 

const H265LevelDescriptor *ff_h265_guess_level(const H265RawProfileTierLevel *ptl,
                                               int64_t bitrate,
                                               int width, int height,
                                               int slice_segments,
                                               int tile_rows, int tile_cols,
                                               int max_dec_pic_buffering)
{
    const H265ProfileDescriptor *profile;
    int pic_size, tier_flag, lbr_flag, hbr_factor;
    int i;

    if (ptl)
        profile = ff_h265_get_profile(ptl);
    else
        profile = NULL;
    if (!profile) {
        // Default to using multiplication factors for Main profile.
        profile = &h265_profiles[3];
    }

    pic_size = width * height;

    if (ptl) {
        tier_flag = ptl->general_tier_flag;
        lbr_flag  = ptl->general_lower_bit_rate_constraint_flag;
    } else {
        tier_flag = 0;
        lbr_flag  = profile->lower_bit_rate > 0;
    }
    if (profile->profile_idc == 1 || profile->profile_idc == 2) {
        hbr_factor = 1;
    } else if (profile->high_throughput) {
        if (profile->intra)
            hbr_factor = 24 - 12 * lbr_flag;
        else
            hbr_factor = 6;
    } else {
        hbr_factor = 2 - lbr_flag;
    }

    for (i = 0; i < FF_ARRAY_ELEMS(h265_levels); i++) {
        const H265LevelDescriptor *level = &h265_levels[i];
        int max_br, max_dpb_size;

        if (tier_flag && !level->max_br_high)
            continue;

        if (pic_size > level->max_luma_ps)
            continue;
        if (width  * width  > 8 * level->max_luma_ps)
            continue;
        if (height * height > 8 * level->max_luma_ps)
            continue;

        if (slice_segments > level->max_slice_segments_per_picture)
            continue;
        if (tile_rows > level->max_tile_rows)
            continue;
        if (tile_cols > level->max_tile_cols)
            continue;

        if (tier_flag)
            max_br = level->max_br_high;
        else
            max_br = level->max_br_main;
        if (!max_br)
            continue;
        if (bitrate > (int64_t)profile->cpb_nal_factor * hbr_factor * max_br)
            continue;

        if (pic_size <= (level->max_luma_ps >> 2))
            max_dpb_size = FFMIN(4 * profile->max_dpb_pic_buf, 16);
        else if (pic_size <= (level->max_luma_ps >> 1))
            max_dpb_size = FFMIN(2 * profile->max_dpb_pic_buf, 16);
        else if (pic_size <= (3 * level->max_luma_ps >> 2))
            max_dpb_size = FFMIN(4 * profile->max_dpb_pic_buf / 3, 16);
        else
            max_dpb_size = profile->max_dpb_pic_buf;
        if (max_dec_pic_buffering > max_dpb_size)
            continue;

        return level;
    }

    return NULL;
}
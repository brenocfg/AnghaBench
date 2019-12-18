#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_5__ {int max_fs; int max_dpb_mbs; int max_mbps; scalar_t__ max_br; scalar_t__ constraint_set3_flag; } ;
typedef  TYPE_1__ H264LevelDescriptor ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int FF_ARRAY_ELEMS (TYPE_1__*) ; 
 int h264_get_br_factor (int) ; 
 TYPE_1__* h264_levels ; 

const H264LevelDescriptor *ff_h264_guess_level(int profile_idc,
                                               int64_t bitrate,
                                               int framerate,
                                               int width, int height,
                                               int max_dec_frame_buffering)
{
    int width_mbs  = (width  + 15) / 16;
    int height_mbs = (height + 15) / 16;
    int no_cs3f = !(profile_idc == 66 ||
                    profile_idc == 77 ||
                    profile_idc == 88);
    int i;

    for (i = 0; i < FF_ARRAY_ELEMS(h264_levels); i++) {
        const H264LevelDescriptor *level = &h264_levels[i];

        if (level->constraint_set3_flag && no_cs3f)
            continue;

        if (bitrate > (int64_t)level->max_br * h264_get_br_factor(profile_idc))
            continue;

        if (width_mbs  * height_mbs > level->max_fs)
            continue;
        if (width_mbs  * width_mbs  > 8 * level->max_fs)
            continue;
        if (height_mbs * height_mbs > 8 * level->max_fs)
            continue;

        if (width_mbs && height_mbs) {
            int max_dpb_frames =
                FFMIN(level->max_dpb_mbs / (width_mbs * height_mbs), 16);
            if (max_dec_frame_buffering > max_dpb_frames)
                continue;

            if (framerate > (level->max_mbps / (width_mbs * height_mbs)))
                continue;
        }

        return level;
    }

    // No usable levels found - frame is too big or bitrate is too high.
    return NULL;
}
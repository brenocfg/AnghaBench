#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
typedef  int /*<<< orphan*/  AVRational ;
typedef  int /*<<< orphan*/  AVDVProfile ;

/* Variables and functions */

const AVDVProfile *av_dv_codec_profile2(int width, int height,
                                       enum AVPixelFormat pix_fmt,
                                       AVRational frame_rate)
{
    const AVDVProfile *p = NULL;
#if CONFIG_DVPROFILE
    int i;
    /* frame rate is necessary to select between 720p50 and 720p60 profiles */
    int invalid_framerate = frame_rate.num == 0 || frame_rate.den == 0;

    for (i = 0; i < FF_ARRAY_ELEMS(dv_profiles); i++)
        if (height  == dv_profiles[i].height  &&
            pix_fmt == dv_profiles[i].pix_fmt &&
            width   == dv_profiles[i].width)
        {
            if( invalid_framerate || av_div_q(dv_profiles[i].time_base, frame_rate).num == 1 )
                return &dv_profiles[i];

            if(!p)
                p = &dv_profiles[i];
        }
#endif

    return p;
}
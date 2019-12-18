#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_11__ {int num; } ;
struct TYPE_10__ {int height; int pix_fmt; int width; int /*<<< orphan*/  time_base; } ;
struct TYPE_9__ {scalar_t__ num; scalar_t__ den; } ;
typedef  TYPE_1__ AVRational ;
typedef  TYPE_2__ AVDVProfile ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (TYPE_2__ const*) ; 
 TYPE_6__ av_div_q (int /*<<< orphan*/ ,TYPE_1__) ; 
 TYPE_2__ const* dv_profiles ; 

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
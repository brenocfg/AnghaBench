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
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
#define  HB_VCODEC_FFMPEG_NVENC_H264 131 
#define  HB_VCODEC_FFMPEG_NVENC_H265 130 
#define  HB_VCODEC_FFMPEG_VP8 129 
#define  HB_VCODEC_FFMPEG_VP9 128 
 int apply_vp8_preset (int /*<<< orphan*/ **,char const*) ; 
 int apply_vp9_preset (int /*<<< orphan*/ **,char const*) ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ **,char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apply_encoder_preset(int vcodec, AVDictionary ** av_opts,
                                const char * preset)
{
    switch (vcodec)
    {
        case HB_VCODEC_FFMPEG_VP8:
            return apply_vp8_preset(av_opts, preset);
        case HB_VCODEC_FFMPEG_VP9:
            return apply_vp9_preset(av_opts, preset);
        case HB_VCODEC_FFMPEG_NVENC_H264:
        case HB_VCODEC_FFMPEG_NVENC_H265:
             av_dict_set( av_opts, "preset", preset, 0);
             break;
        default:
            break;
    }

    return 0;
}
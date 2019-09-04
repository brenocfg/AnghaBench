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
typedef  int /*<<< orphan*/  VdpDecoderProfile ;
struct TYPE_3__ {int codec_id; int profile; } ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_CODEC_ID_H263 145 
#define  AV_CODEC_ID_H264 144 
#define  AV_CODEC_ID_MPEG1VIDEO 143 
#define  AV_CODEC_ID_MPEG2VIDEO 142 
#define  AV_CODEC_ID_MPEG4 141 
#define  AV_CODEC_ID_VC1 140 
#define  AV_CODEC_ID_WMV3 139 
 int /*<<< orphan*/  EINVAL ; 
#define  FF_PROFILE_H264_BASELINE 138 
#define  FF_PROFILE_H264_CONSTRAINED_BASELINE 137 
#define  FF_PROFILE_H264_HIGH 136 
 int FF_PROFILE_H264_INTRA ; 
#define  FF_PROFILE_H264_MAIN 135 
#define  FF_PROFILE_MPEG2_MAIN 134 
#define  FF_PROFILE_MPEG2_SIMPLE 133 
#define  FF_PROFILE_MPEG4_ADVANCED_SIMPLE 132 
#define  FF_PROFILE_MPEG4_SIMPLE 131 
#define  FF_PROFILE_VC1_ADVANCED 130 
#define  FF_PROFILE_VC1_MAIN 129 
#define  FF_PROFILE_VC1_SIMPLE 128 
 int /*<<< orphan*/  VDP_DECODER_PROFILE_H264_BASELINE ; 
 int /*<<< orphan*/  VDP_DECODER_PROFILE_H264_HIGH ; 
 int /*<<< orphan*/  VDP_DECODER_PROFILE_H264_MAIN ; 
 int /*<<< orphan*/  VDP_DECODER_PROFILE_MPEG1 ; 
 int /*<<< orphan*/  VDP_DECODER_PROFILE_MPEG2_MAIN ; 
 int /*<<< orphan*/  VDP_DECODER_PROFILE_MPEG2_SIMPLE ; 
 int /*<<< orphan*/  VDP_DECODER_PROFILE_MPEG4_PART2_ASP ; 
 int /*<<< orphan*/  VDP_DECODER_PROFILE_MPEG4_PART2_SP ; 
 int /*<<< orphan*/  VDP_DECODER_PROFILE_VC1_ADVANCED ; 
 int /*<<< orphan*/  VDP_DECODER_PROFILE_VC1_MAIN ; 
 int /*<<< orphan*/  VDP_DECODER_PROFILE_VC1_SIMPLE ; 

int av_vdpau_get_profile(AVCodecContext *avctx, VdpDecoderProfile *profile)
{
#define PROFILE(prof)                      \
do {                                       \
    *profile = VDP_DECODER_PROFILE_##prof; \
    return 0;                              \
} while (0)

    switch (avctx->codec_id) {
    case AV_CODEC_ID_MPEG1VIDEO:               PROFILE(MPEG1);
    case AV_CODEC_ID_MPEG2VIDEO:
        switch (avctx->profile) {
        case FF_PROFILE_MPEG2_MAIN:            PROFILE(MPEG2_MAIN);
        case FF_PROFILE_MPEG2_SIMPLE:          PROFILE(MPEG2_SIMPLE);
        default:                               return AVERROR(EINVAL);
        }
    case AV_CODEC_ID_H263:                     PROFILE(MPEG4_PART2_ASP);
    case AV_CODEC_ID_MPEG4:
        switch (avctx->profile) {
        case FF_PROFILE_MPEG4_SIMPLE:          PROFILE(MPEG4_PART2_SP);
        case FF_PROFILE_MPEG4_ADVANCED_SIMPLE: PROFILE(MPEG4_PART2_ASP);
        default:                               return AVERROR(EINVAL);
        }
    case AV_CODEC_ID_H264:
        switch (avctx->profile & ~FF_PROFILE_H264_INTRA) {
        case FF_PROFILE_H264_BASELINE:         PROFILE(H264_BASELINE);
        case FF_PROFILE_H264_CONSTRAINED_BASELINE:
        case FF_PROFILE_H264_MAIN:             PROFILE(H264_MAIN);
        case FF_PROFILE_H264_HIGH:             PROFILE(H264_HIGH);
#ifdef VDP_DECODER_PROFILE_H264_EXTENDED
        case FF_PROFILE_H264_EXTENDED:         PROFILE(H264_EXTENDED);
#endif
        default:                               return AVERROR(EINVAL);
        }
    case AV_CODEC_ID_WMV3:
    case AV_CODEC_ID_VC1:
        switch (avctx->profile) {
        case FF_PROFILE_VC1_SIMPLE:            PROFILE(VC1_SIMPLE);
        case FF_PROFILE_VC1_MAIN:              PROFILE(VC1_MAIN);
        case FF_PROFILE_VC1_ADVANCED:          PROFILE(VC1_ADVANCED);
        default:                               return AVERROR(EINVAL);
        }
    }
    return AVERROR(EINVAL);
#undef PROFILE
}
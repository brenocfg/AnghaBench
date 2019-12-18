#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  VdpDecoderProfile ;
struct TYPE_4__ {int level; int profile; } ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOTSUP ; 
#define  FF_PROFILE_H264_BASELINE 136 
#define  FF_PROFILE_H264_CAVLC_444 135 
#define  FF_PROFILE_H264_CONSTRAINED_BASELINE 134 
#define  FF_PROFILE_H264_EXTENDED 133 
#define  FF_PROFILE_H264_HIGH 132 
#define  FF_PROFILE_H264_HIGH_10 131 
#define  FF_PROFILE_H264_HIGH_422 130 
#define  FF_PROFILE_H264_HIGH_444_PREDICTIVE 129 
 int FF_PROFILE_H264_INTRA ; 
#define  FF_PROFILE_H264_MAIN 128 
 int VDP_DECODER_LEVEL_H264_1b ; 
 int /*<<< orphan*/  VDP_DECODER_PROFILE_H264_BASELINE ; 
 int /*<<< orphan*/  VDP_DECODER_PROFILE_H264_CONSTRAINED_BASELINE ; 
 int /*<<< orphan*/  VDP_DECODER_PROFILE_H264_EXTENDED ; 
 int /*<<< orphan*/  VDP_DECODER_PROFILE_H264_HIGH ; 
 int /*<<< orphan*/  VDP_DECODER_PROFILE_H264_HIGH_444_PREDICTIVE ; 
 int /*<<< orphan*/  VDP_DECODER_PROFILE_H264_MAIN ; 
 int ff_vdpau_common_init (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vdpau_h264_init(AVCodecContext *avctx)
{
    VdpDecoderProfile profile;
    uint32_t level = avctx->level;

    switch (avctx->profile & ~FF_PROFILE_H264_INTRA) {
    case FF_PROFILE_H264_BASELINE:
        profile = VDP_DECODER_PROFILE_H264_BASELINE;
        break;
    case FF_PROFILE_H264_CONSTRAINED_BASELINE:
#ifdef VDP_DECODER_PROFILE_H264_CONSTRAINED_BASELINE
        profile = VDP_DECODER_PROFILE_H264_CONSTRAINED_BASELINE;
        break;
#endif
    case FF_PROFILE_H264_MAIN:
        profile = VDP_DECODER_PROFILE_H264_MAIN;
        break;
    case FF_PROFILE_H264_HIGH:
        profile = VDP_DECODER_PROFILE_H264_HIGH;
        break;
#ifdef VDP_DECODER_PROFILE_H264_EXTENDED
    case FF_PROFILE_H264_EXTENDED:
        profile = VDP_DECODER_PROFILE_H264_EXTENDED;
        break;
#endif
    case FF_PROFILE_H264_HIGH_10:
        /* XXX: High 10 can be treated as High so long as only 8 bits per
         * format are supported. */
        profile = VDP_DECODER_PROFILE_H264_HIGH;
        break;
#ifdef VDP_DECODER_PROFILE_H264_HIGH_444_PREDICTIVE
    case FF_PROFILE_H264_HIGH_422:
    case FF_PROFILE_H264_HIGH_444_PREDICTIVE:
    case FF_PROFILE_H264_CAVLC_444:
        profile = VDP_DECODER_PROFILE_H264_HIGH_444_PREDICTIVE;
        break;
#endif
    default:
        return AVERROR(ENOTSUP);
    }

    if ((avctx->profile & FF_PROFILE_H264_INTRA) && avctx->level == 11)
        level = VDP_DECODER_LEVEL_H264_1b;

    return ff_vdpau_common_init(avctx, profile, level);
}
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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  VdpDecoderProfile ;
struct TYPE_4__ {int profile; int /*<<< orphan*/  level; } ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOTSUP ; 
#define  FF_PROFILE_HEVC_MAIN 131 
#define  FF_PROFILE_HEVC_MAIN_10 130 
#define  FF_PROFILE_HEVC_MAIN_STILL_PICTURE 129 
#define  FF_PROFILE_HEVC_REXT 128 
 int /*<<< orphan*/  VDP_DECODER_PROFILE_HEVC_MAIN ; 
 int /*<<< orphan*/  VDP_DECODER_PROFILE_HEVC_MAIN_10 ; 
 int /*<<< orphan*/  VDP_DECODER_PROFILE_HEVC_MAIN_444 ; 
 int /*<<< orphan*/  VDP_DECODER_PROFILE_HEVC_MAIN_STILL ; 
 int ff_vdpau_common_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vdpau_hevc_init(AVCodecContext *avctx)
{
    VdpDecoderProfile profile;
    uint32_t level = avctx->level;

    switch (avctx->profile) {
    case FF_PROFILE_HEVC_MAIN:
        profile = VDP_DECODER_PROFILE_HEVC_MAIN;
        break;
    case FF_PROFILE_HEVC_MAIN_10:
        profile = VDP_DECODER_PROFILE_HEVC_MAIN_10;
        break;
    case FF_PROFILE_HEVC_MAIN_STILL_PICTURE:
        profile = VDP_DECODER_PROFILE_HEVC_MAIN_STILL;
        break;
    case FF_PROFILE_HEVC_REXT:
        profile = VDP_DECODER_PROFILE_HEVC_MAIN_444;
        break;
    default:
        return AVERROR(ENOTSUP);
    }

    return ff_vdpau_common_init(avctx, profile, level);
}
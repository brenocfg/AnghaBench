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
typedef  int /*<<< orphan*/  VdpDecoderProfile ;
struct TYPE_4__ {int profile; int /*<<< orphan*/  level; } ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOTSUP ; 
#define  FF_PROFILE_VC1_ADVANCED 130 
#define  FF_PROFILE_VC1_MAIN 129 
#define  FF_PROFILE_VC1_SIMPLE 128 
 int /*<<< orphan*/  VDP_DECODER_PROFILE_VC1_ADVANCED ; 
 int /*<<< orphan*/  VDP_DECODER_PROFILE_VC1_MAIN ; 
 int /*<<< orphan*/  VDP_DECODER_PROFILE_VC1_SIMPLE ; 
 int ff_vdpau_common_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vdpau_vc1_init(AVCodecContext *avctx)
{
    VdpDecoderProfile profile;

    switch (avctx->profile) {
    case FF_PROFILE_VC1_SIMPLE:
        profile = VDP_DECODER_PROFILE_VC1_SIMPLE;
        break;
    case FF_PROFILE_VC1_MAIN:
        profile = VDP_DECODER_PROFILE_VC1_MAIN;
        break;
    case FF_PROFILE_VC1_ADVANCED:
        profile = VDP_DECODER_PROFILE_VC1_ADVANCED;
        break;
    default:
        return AVERROR(ENOTSUP);
    }

    return ff_vdpau_common_init(avctx, profile, avctx->level);
}
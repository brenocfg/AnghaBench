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
struct TYPE_3__ {int codec_id; } ;
typedef  int /*<<< orphan*/  MppCodingType ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
#define  AV_CODEC_ID_H264 131 
#define  AV_CODEC_ID_HEVC 130 
#define  AV_CODEC_ID_VP8 129 
#define  AV_CODEC_ID_VP9 128 
 int /*<<< orphan*/  MPP_VIDEO_CodingAVC ; 
 int /*<<< orphan*/  MPP_VIDEO_CodingHEVC ; 
 int /*<<< orphan*/  MPP_VIDEO_CodingUnused ; 
 int /*<<< orphan*/  MPP_VIDEO_CodingVP8 ; 
 int /*<<< orphan*/  MPP_VIDEO_CodingVP9 ; 

__attribute__((used)) static MppCodingType rkmpp_get_codingtype(AVCodecContext *avctx)
{
    switch (avctx->codec_id) {
    case AV_CODEC_ID_H264:          return MPP_VIDEO_CodingAVC;
    case AV_CODEC_ID_HEVC:          return MPP_VIDEO_CodingHEVC;
    case AV_CODEC_ID_VP8:           return MPP_VIDEO_CodingVP8;
    case AV_CODEC_ID_VP9:           return MPP_VIDEO_CodingVP9;
    default:                        return MPP_VIDEO_CodingUnused;
    }
}
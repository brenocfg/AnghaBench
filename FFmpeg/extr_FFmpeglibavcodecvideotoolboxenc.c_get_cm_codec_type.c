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
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
typedef  int /*<<< orphan*/  CMVideoCodecType ;

/* Variables and functions */
#define  AV_CODEC_ID_H264 129 
#define  AV_CODEC_ID_HEVC 128 
 int /*<<< orphan*/  kCMVideoCodecType_H264 ; 
 int /*<<< orphan*/  kCMVideoCodecType_HEVC ; 

__attribute__((used)) static CMVideoCodecType get_cm_codec_type(enum AVCodecID id)
{
    switch (id) {
    case AV_CODEC_ID_H264: return kCMVideoCodecType_H264;
    case AV_CODEC_ID_HEVC: return kCMVideoCodecType_HEVC;
    default:               return 0;
    }
}
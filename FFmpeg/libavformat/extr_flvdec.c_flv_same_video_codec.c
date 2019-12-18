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
struct TYPE_3__ {int codec_tag; int /*<<< orphan*/  codec_id; } ;
typedef  TYPE_1__ AVCodecParameters ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CODEC_ID_FLASHSV ; 
 int /*<<< orphan*/  AV_CODEC_ID_FLASHSV2 ; 
 int /*<<< orphan*/  AV_CODEC_ID_FLV1 ; 
 int /*<<< orphan*/  AV_CODEC_ID_H264 ; 
 int /*<<< orphan*/  AV_CODEC_ID_VP6A ; 
 int /*<<< orphan*/  AV_CODEC_ID_VP6F ; 
#define  FLV_CODECID_H263 133 
#define  FLV_CODECID_H264 132 
#define  FLV_CODECID_SCREEN 131 
#define  FLV_CODECID_SCREEN2 130 
#define  FLV_CODECID_VP6 129 
#define  FLV_CODECID_VP6A 128 
 int FLV_VIDEO_CODECID_MASK ; 

__attribute__((used)) static int flv_same_video_codec(AVCodecParameters *vpar, int flags)
{
    int flv_codecid = flags & FLV_VIDEO_CODECID_MASK;

    if (!vpar->codec_id && !vpar->codec_tag)
        return 1;

    switch (flv_codecid) {
    case FLV_CODECID_H263:
        return vpar->codec_id == AV_CODEC_ID_FLV1;
    case FLV_CODECID_SCREEN:
        return vpar->codec_id == AV_CODEC_ID_FLASHSV;
    case FLV_CODECID_SCREEN2:
        return vpar->codec_id == AV_CODEC_ID_FLASHSV2;
    case FLV_CODECID_VP6:
        return vpar->codec_id == AV_CODEC_ID_VP6F;
    case FLV_CODECID_VP6A:
        return vpar->codec_id == AV_CODEC_ID_VP6A;
    case FLV_CODECID_H264:
        return vpar->codec_id == AV_CODEC_ID_H264;
    default:
        return vpar->codec_tag == flv_codecid;
    }
}
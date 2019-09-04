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
typedef  int /*<<< orphan*/  CHDContext ;
typedef  int /*<<< orphan*/  BC_MEDIA_SUBTYPE ;

/* Variables and functions */
#define  AV_CODEC_ID_H264 133 
#define  AV_CODEC_ID_MPEG2VIDEO 132 
#define  AV_CODEC_ID_MPEG4 131 
#define  AV_CODEC_ID_MSMPEG4V3 130 
#define  AV_CODEC_ID_VC1 129 
#define  AV_CODEC_ID_WMV3 128 
 int /*<<< orphan*/  BC_MSUBTYPE_DIVX ; 
 int /*<<< orphan*/  BC_MSUBTYPE_DIVX311 ; 
 int /*<<< orphan*/  BC_MSUBTYPE_H264 ; 
 int /*<<< orphan*/  BC_MSUBTYPE_INVALID ; 
 int /*<<< orphan*/  BC_MSUBTYPE_MPEG2VIDEO ; 
 int /*<<< orphan*/  BC_MSUBTYPE_VC1 ; 
 int /*<<< orphan*/  BC_MSUBTYPE_WMV3 ; 

__attribute__((used)) static inline BC_MEDIA_SUBTYPE id2subtype(CHDContext *priv, enum AVCodecID id)
{
    switch (id) {
    case AV_CODEC_ID_MPEG4:
        return BC_MSUBTYPE_DIVX;
    case AV_CODEC_ID_MSMPEG4V3:
        return BC_MSUBTYPE_DIVX311;
    case AV_CODEC_ID_MPEG2VIDEO:
        return BC_MSUBTYPE_MPEG2VIDEO;
    case AV_CODEC_ID_VC1:
        return BC_MSUBTYPE_VC1;
    case AV_CODEC_ID_WMV3:
        return BC_MSUBTYPE_WMV3;
    case AV_CODEC_ID_H264:
        return BC_MSUBTYPE_H264;
    default:
        return BC_MSUBTYPE_INVALID;
    }
}
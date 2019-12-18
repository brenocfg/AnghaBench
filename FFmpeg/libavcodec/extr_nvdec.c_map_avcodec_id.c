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

/* Variables and functions */
#define  AV_CODEC_ID_H264 137 
#define  AV_CODEC_ID_HEVC 136 
#define  AV_CODEC_ID_MJPEG 135 
#define  AV_CODEC_ID_MPEG1VIDEO 134 
#define  AV_CODEC_ID_MPEG2VIDEO 133 
#define  AV_CODEC_ID_MPEG4 132 
#define  AV_CODEC_ID_VC1 131 
#define  AV_CODEC_ID_VP8 130 
#define  AV_CODEC_ID_VP9 129 
#define  AV_CODEC_ID_WMV3 128 
 int cudaVideoCodec_H264 ; 
 int cudaVideoCodec_HEVC ; 
 int cudaVideoCodec_JPEG ; 
 int cudaVideoCodec_MPEG1 ; 
 int cudaVideoCodec_MPEG2 ; 
 int cudaVideoCodec_MPEG4 ; 
 int cudaVideoCodec_VC1 ; 
 int cudaVideoCodec_VP8 ; 
 int cudaVideoCodec_VP9 ; 

__attribute__((used)) static int map_avcodec_id(enum AVCodecID id)
{
    switch (id) {
    case AV_CODEC_ID_H264:       return cudaVideoCodec_H264;
    case AV_CODEC_ID_HEVC:       return cudaVideoCodec_HEVC;
    case AV_CODEC_ID_MJPEG:      return cudaVideoCodec_JPEG;
    case AV_CODEC_ID_MPEG1VIDEO: return cudaVideoCodec_MPEG1;
    case AV_CODEC_ID_MPEG2VIDEO: return cudaVideoCodec_MPEG2;
    case AV_CODEC_ID_MPEG4:      return cudaVideoCodec_MPEG4;
    case AV_CODEC_ID_VC1:        return cudaVideoCodec_VC1;
    case AV_CODEC_ID_VP8:        return cudaVideoCodec_VP8;
    case AV_CODEC_ID_VP9:        return cudaVideoCodec_VP9;
    case AV_CODEC_ID_WMV3:       return cudaVideoCodec_VC1;
    }
    return -1;
}
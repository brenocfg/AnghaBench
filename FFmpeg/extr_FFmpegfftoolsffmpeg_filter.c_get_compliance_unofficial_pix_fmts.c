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
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;

/* Variables and functions */
 int AV_CODEC_ID_LJPEG ; 
 int AV_CODEC_ID_MJPEG ; 
#define  AV_PIX_FMT_BGR0 137 
#define  AV_PIX_FMT_BGR24 136 
#define  AV_PIX_FMT_BGRA 135 
#define  AV_PIX_FMT_NONE 134 
#define  AV_PIX_FMT_YUV420P 133 
#define  AV_PIX_FMT_YUV422P 132 
#define  AV_PIX_FMT_YUV444P 131 
#define  AV_PIX_FMT_YUVJ420P 130 
#define  AV_PIX_FMT_YUVJ422P 129 
#define  AV_PIX_FMT_YUVJ444P 128 

__attribute__((used)) static const enum AVPixelFormat *get_compliance_unofficial_pix_fmts(enum AVCodecID codec_id, const enum AVPixelFormat default_formats[])
{
    static const enum AVPixelFormat mjpeg_formats[] =
        { AV_PIX_FMT_YUVJ420P, AV_PIX_FMT_YUVJ422P, AV_PIX_FMT_YUVJ444P,
          AV_PIX_FMT_YUV420P,  AV_PIX_FMT_YUV422P,  AV_PIX_FMT_YUV444P,
          AV_PIX_FMT_NONE };
    static const enum AVPixelFormat ljpeg_formats[] =
        { AV_PIX_FMT_BGR24   , AV_PIX_FMT_BGRA    , AV_PIX_FMT_BGR0,
          AV_PIX_FMT_YUVJ420P, AV_PIX_FMT_YUVJ444P, AV_PIX_FMT_YUVJ422P,
          AV_PIX_FMT_YUV420P , AV_PIX_FMT_YUV444P , AV_PIX_FMT_YUV422P,
          AV_PIX_FMT_NONE};

    if (codec_id == AV_CODEC_ID_MJPEG) {
        return mjpeg_formats;
    } else if (codec_id == AV_CODEC_ID_LJPEG) {
        return ljpeg_formats;
    } else {
        return default_formats;
    }
}
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

/* Variables and functions */
#define  AV_PIX_FMT_NV12 141 
#define  AV_PIX_FMT_NV16 140 
#define  AV_PIX_FMT_NV20 139 
#define  AV_PIX_FMT_YUV420P 138 
#define  AV_PIX_FMT_YUV420P10 137 
#define  AV_PIX_FMT_YUV420P9 136 
#define  AV_PIX_FMT_YUV422P 135 
#define  AV_PIX_FMT_YUV422P10 134 
#define  AV_PIX_FMT_YUV444P 133 
#define  AV_PIX_FMT_YUV444P10 132 
#define  AV_PIX_FMT_YUV444P9 131 
#define  AV_PIX_FMT_YUVJ420P 130 
#define  AV_PIX_FMT_YUVJ422P 129 
#define  AV_PIX_FMT_YUVJ444P 128 
 int X264_CSP_I420 ; 
 int X264_CSP_I422 ; 
 int X264_CSP_I444 ; 
 int X264_CSP_NV12 ; 
 int X264_CSP_NV16 ; 

__attribute__((used)) static int convert_pix_fmt(enum AVPixelFormat pix_fmt)
{
    switch (pix_fmt) {
    case AV_PIX_FMT_YUV420P:
    case AV_PIX_FMT_YUVJ420P:
    case AV_PIX_FMT_YUV420P9:
    case AV_PIX_FMT_YUV420P10: return X264_CSP_I420;
    case AV_PIX_FMT_YUV422P:
    case AV_PIX_FMT_YUVJ422P:
    case AV_PIX_FMT_YUV422P10: return X264_CSP_I422;
    case AV_PIX_FMT_YUV444P:
    case AV_PIX_FMT_YUVJ444P:
    case AV_PIX_FMT_YUV444P9:
    case AV_PIX_FMT_YUV444P10: return X264_CSP_I444;
#if CONFIG_LIBX264RGB_ENCODER
    case AV_PIX_FMT_BGR0:
        return X264_CSP_BGRA;
    case AV_PIX_FMT_BGR24:
        return X264_CSP_BGR;

    case AV_PIX_FMT_RGB24:
        return X264_CSP_RGB;
#endif
    case AV_PIX_FMT_NV12:      return X264_CSP_NV12;
    case AV_PIX_FMT_NV16:
    case AV_PIX_FMT_NV20:      return X264_CSP_NV16;
#ifdef X264_CSP_NV21
    case AV_PIX_FMT_NV21:      return X264_CSP_NV21;
#endif
#ifdef X264_CSP_I400
    case AV_PIX_FMT_GRAY8:
    case AV_PIX_FMT_GRAY10:    return X264_CSP_I400;
#endif
    };
    return 0;
}
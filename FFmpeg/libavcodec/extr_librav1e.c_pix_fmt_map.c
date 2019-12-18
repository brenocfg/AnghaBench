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
typedef  int /*<<< orphan*/  RaChromaSampling ;

/* Variables and functions */
#define  AV_PIX_FMT_YUV420P 139 
#define  AV_PIX_FMT_YUV420P10 138 
#define  AV_PIX_FMT_YUV420P12 137 
#define  AV_PIX_FMT_YUV422P 136 
#define  AV_PIX_FMT_YUV422P10 135 
#define  AV_PIX_FMT_YUV422P12 134 
#define  AV_PIX_FMT_YUV444P 133 
#define  AV_PIX_FMT_YUV444P10 132 
#define  AV_PIX_FMT_YUV444P12 131 
#define  AV_PIX_FMT_YUVJ420P 130 
#define  AV_PIX_FMT_YUVJ422P 129 
#define  AV_PIX_FMT_YUVJ444P 128 
 int /*<<< orphan*/  RA_CHROMA_SAMPLING_CS420 ; 
 int /*<<< orphan*/  RA_CHROMA_SAMPLING_CS422 ; 
 int /*<<< orphan*/  RA_CHROMA_SAMPLING_CS444 ; 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline RaChromaSampling pix_fmt_map(enum AVPixelFormat pix_fmt)
{
    switch (pix_fmt) {
    case AV_PIX_FMT_YUV420P:
    case AV_PIX_FMT_YUVJ420P:
    case AV_PIX_FMT_YUV420P10:
    case AV_PIX_FMT_YUV420P12:
        return RA_CHROMA_SAMPLING_CS420;
    case AV_PIX_FMT_YUV422P:
    case AV_PIX_FMT_YUVJ422P:
    case AV_PIX_FMT_YUV422P10:
    case AV_PIX_FMT_YUV422P12:
        return RA_CHROMA_SAMPLING_CS422;
    case AV_PIX_FMT_YUV444P:
    case AV_PIX_FMT_YUVJ444P:
    case AV_PIX_FMT_YUV444P10:
    case AV_PIX_FMT_YUV444P12:
        return RA_CHROMA_SAMPLING_CS444;
    default:
        av_assert0(0);
    }
}
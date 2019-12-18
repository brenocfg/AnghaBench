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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_PIX_FMT_NV12 132 
#define  AV_PIX_FMT_P010 131 
#define  AV_PIX_FMT_YUV420P 130 
#define  AV_PIX_FMT_YUV420P10 129 
#define  AV_PIX_FMT_YUVJ420P 128 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  MFX_FOURCC_NV12 ; 
 int /*<<< orphan*/  MFX_FOURCC_P010 ; 

int ff_qsv_map_pixfmt(enum AVPixelFormat format, uint32_t *fourcc)
{
    switch (format) {
    case AV_PIX_FMT_YUV420P:
    case AV_PIX_FMT_YUVJ420P:
    case AV_PIX_FMT_NV12:
        *fourcc = MFX_FOURCC_NV12;
        return AV_PIX_FMT_NV12;
    case AV_PIX_FMT_YUV420P10:
    case AV_PIX_FMT_P010:
        *fourcc = MFX_FOURCC_P010;
        return AV_PIX_FMT_P010;
    default:
        return AVERROR(ENOSYS);
    }
}
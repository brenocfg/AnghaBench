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
typedef  int /*<<< orphan*/  NV_ENC_BUFFER_FORMAT ;

/* Variables and functions */
#define  AV_PIX_FMT_0BGR32 135 
#define  AV_PIX_FMT_0RGB32 134 
#define  AV_PIX_FMT_NV12 133 
#define  AV_PIX_FMT_P010 132 
#define  AV_PIX_FMT_P016 131 
#define  AV_PIX_FMT_YUV420P 130 
#define  AV_PIX_FMT_YUV444P 129 
#define  AV_PIX_FMT_YUV444P16 128 
 int /*<<< orphan*/  NV_ENC_BUFFER_FORMAT_ABGR ; 
 int /*<<< orphan*/  NV_ENC_BUFFER_FORMAT_ARGB ; 
 int /*<<< orphan*/  NV_ENC_BUFFER_FORMAT_NV12_PL ; 
 int /*<<< orphan*/  NV_ENC_BUFFER_FORMAT_UNDEFINED ; 
 int /*<<< orphan*/  NV_ENC_BUFFER_FORMAT_YUV420_10BIT ; 
 int /*<<< orphan*/  NV_ENC_BUFFER_FORMAT_YUV444_10BIT ; 
 int /*<<< orphan*/  NV_ENC_BUFFER_FORMAT_YUV444_PL ; 
 int /*<<< orphan*/  NV_ENC_BUFFER_FORMAT_YV12_PL ; 

__attribute__((used)) static NV_ENC_BUFFER_FORMAT nvenc_map_buffer_format(enum AVPixelFormat pix_fmt)
{
    switch (pix_fmt) {
    case AV_PIX_FMT_YUV420P:
        return NV_ENC_BUFFER_FORMAT_YV12_PL;
    case AV_PIX_FMT_NV12:
        return NV_ENC_BUFFER_FORMAT_NV12_PL;
    case AV_PIX_FMT_P010:
    case AV_PIX_FMT_P016:
        return NV_ENC_BUFFER_FORMAT_YUV420_10BIT;
    case AV_PIX_FMT_YUV444P:
        return NV_ENC_BUFFER_FORMAT_YUV444_PL;
    case AV_PIX_FMT_YUV444P16:
        return NV_ENC_BUFFER_FORMAT_YUV444_10BIT;
    case AV_PIX_FMT_0RGB32:
        return NV_ENC_BUFFER_FORMAT_ARGB;
    case AV_PIX_FMT_0BGR32:
        return NV_ENC_BUFFER_FORMAT_ABGR;
    default:
        return NV_ENC_BUFFER_FORMAT_UNDEFINED;
    }
}
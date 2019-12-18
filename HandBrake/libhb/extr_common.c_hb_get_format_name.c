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

/* Variables and functions */
#define  AV_PIX_FMT_YUV420P 136 
#define  AV_PIX_FMT_YUV420P10 135 
#define  AV_PIX_FMT_YUV420P12 134 
#define  AV_PIX_FMT_YUV422P 133 
#define  AV_PIX_FMT_YUV422P10 132 
#define  AV_PIX_FMT_YUV422P12 131 
#define  AV_PIX_FMT_YUV444P 130 
#define  AV_PIX_FMT_YUV444P10 129 
#define  AV_PIX_FMT_YUV444P12 128 

const char * hb_get_format_name(int format)
{
    switch (format)
    {
        case AV_PIX_FMT_YUV420P:
            return "yuv420p";
        case AV_PIX_FMT_YUV420P10:
            return "yuv420p10";
        case AV_PIX_FMT_YUV420P12:
            return "yuv420p12";
        case AV_PIX_FMT_YUV422P:
            return "yuv422p";
        case AV_PIX_FMT_YUV422P10:
            return "yuv422p10";
        case AV_PIX_FMT_YUV422P12:
            return "yuv422p12";
        case AV_PIX_FMT_YUV444P:
            return "yuv444p";
        case AV_PIX_FMT_YUV444P10:
            return "yuv444p10";
        case AV_PIX_FMT_YUV444P12:
            return "yuv444p12";
        default:
            return NULL;
    }
}
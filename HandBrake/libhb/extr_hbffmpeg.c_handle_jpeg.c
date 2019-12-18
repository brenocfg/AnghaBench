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
 int AV_PIX_FMT_YUV420P ; 
 int AV_PIX_FMT_YUV422P ; 
 int AV_PIX_FMT_YUV440P ; 
 int AV_PIX_FMT_YUV444P ; 
#define  AV_PIX_FMT_YUVJ420P 131 
#define  AV_PIX_FMT_YUVJ422P 130 
#define  AV_PIX_FMT_YUVJ440P 129 
#define  AV_PIX_FMT_YUVJ444P 128 

__attribute__((used)) static int handle_jpeg(enum AVPixelFormat *format)
{
    switch (*format)
    {
        case AV_PIX_FMT_YUVJ420P: *format = AV_PIX_FMT_YUV420P; return 1;
        case AV_PIX_FMT_YUVJ422P: *format = AV_PIX_FMT_YUV422P; return 1;
        case AV_PIX_FMT_YUVJ444P: *format = AV_PIX_FMT_YUV444P; return 1;
        case AV_PIX_FMT_YUVJ440P: *format = AV_PIX_FMT_YUV440P; return 1;
        default:                                                return 0;
    }
}
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
#define  AV_PIX_FMT_BGR0 137 
#define  AV_PIX_FMT_BGR24 136 
#define  AV_PIX_FMT_GRAY10 135 
#define  AV_PIX_FMT_GRAY8 134 
#define  AV_PIX_FMT_RGB24 133 
#define  AV_PIX_FMT_YUV420P 132 
#define  AV_PIX_FMT_YUV420P10 131 
#define  AV_PIX_FMT_YUV420P9 130 
#define  AV_PIX_FMT_YUV444P 129 
#define  AV_PIX_FMT_YUVJ420P 128 

__attribute__((used)) static int avfmt2_num_planes(int avfmt)
{
    switch (avfmt) {
    case AV_PIX_FMT_YUV420P:
    case AV_PIX_FMT_YUVJ420P:
    case AV_PIX_FMT_YUV420P9:
    case AV_PIX_FMT_YUV420P10:
    case AV_PIX_FMT_YUV444P:
        return 3;

    case AV_PIX_FMT_BGR0:
    case AV_PIX_FMT_BGR24:
    case AV_PIX_FMT_RGB24:
    case AV_PIX_FMT_GRAY8:
    case AV_PIX_FMT_GRAY10:
        return 1;

    default:
        return 3;
    }
}
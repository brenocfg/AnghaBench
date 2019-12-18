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
#define  AV_PIX_FMT_BGRA 131 
#define  AV_PIX_FMT_NV12 130 
#define  AV_PIX_FMT_YUV420P 129 
#define  AV_PIX_FMT_YUYV422 128 
 int MFX_FOURCC_NV12 ; 
 int MFX_FOURCC_RGB4 ; 
 int MFX_FOURCC_YUY2 ; 
 int MFX_FOURCC_YV12 ; 

__attribute__((used)) static int pix_fmt_to_mfx_fourcc(int format)
{
    switch (format) {
    case AV_PIX_FMT_YUV420P:
        return MFX_FOURCC_YV12;
    case AV_PIX_FMT_NV12:
        return MFX_FOURCC_NV12;
    case AV_PIX_FMT_YUYV422:
        return MFX_FOURCC_YUY2;
    case AV_PIX_FMT_BGRA:
        return MFX_FOURCC_RGB4;
    }

    return MFX_FOURCC_NV12;
}
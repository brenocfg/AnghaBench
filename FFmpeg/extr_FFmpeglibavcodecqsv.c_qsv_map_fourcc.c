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
typedef  int uint32_t ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;

/* Variables and functions */
 int AV_PIX_FMT_NONE ; 
 int AV_PIX_FMT_NV12 ; 
 int AV_PIX_FMT_P010 ; 
 int AV_PIX_FMT_PAL8 ; 
#define  MFX_FOURCC_NV12 130 
#define  MFX_FOURCC_P010 129 
#define  MFX_FOURCC_P8 128 

__attribute__((used)) static enum AVPixelFormat qsv_map_fourcc(uint32_t fourcc)
{
    switch (fourcc) {
    case MFX_FOURCC_NV12: return AV_PIX_FMT_NV12;
    case MFX_FOURCC_P010: return AV_PIX_FMT_P010;
    case MFX_FOURCC_P8:   return AV_PIX_FMT_PAL8;
    }
    return AV_PIX_FMT_NONE;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int int16_t ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_3__ {int dstFormat; int* chrDither8; } ;
typedef  TYPE_1__ SwsContext ;

/* Variables and functions */
 int AV_PIX_FMT_NV12 ; 
 int AV_PIX_FMT_NV24 ; 
 int av_clip_uint8 (int) ; 

__attribute__((used)) static void yuv2nv12cX_c(SwsContext *c, const int16_t *chrFilter, int chrFilterSize,
                        const int16_t **chrUSrc, const int16_t **chrVSrc,
                        uint8_t *dest, int chrDstW)
{
    enum AVPixelFormat dstFormat = c->dstFormat;
    const uint8_t *chrDither = c->chrDither8;
    int i;

    if (dstFormat == AV_PIX_FMT_NV12 ||
        dstFormat == AV_PIX_FMT_NV24)
        for (i=0; i<chrDstW; i++) {
            int u = chrDither[i & 7] << 12;
            int v = chrDither[(i + 3) & 7] << 12;
            int j;
            for (j=0; j<chrFilterSize; j++) {
                u += chrUSrc[j][i] * chrFilter[j];
                v += chrVSrc[j][i] * chrFilter[j];
            }

            dest[2*i]= av_clip_uint8(u>>19);
            dest[2*i+1]= av_clip_uint8(v>>19);
        }
    else
        for (i=0; i<chrDstW; i++) {
            int u = chrDither[i & 7] << 12;
            int v = chrDither[(i + 3) & 7] << 12;
            int j;
            for (j=0; j<chrFilterSize; j++) {
                u += chrUSrc[j][i] * chrFilter[j];
                v += chrVSrc[j][i] * chrFilter[j];
            }

            dest[2*i]= av_clip_uint8(v>>19);
            dest[2*i+1]= av_clip_uint8(u>>19);
        }
}
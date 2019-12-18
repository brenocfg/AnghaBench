#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {int format; int width; int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_6__ {scalar_t__ v; scalar_t__ u; scalar_t__ y; } ;
struct TYPE_7__ {TYPE_1__ yuv; } ;
typedef  TYPE_2__ ColorFloat ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */
 int AV_PIX_FMT_YUV444P ; 
 void* lrintf (scalar_t__) ; 

__attribute__((used)) static void update_sono_yuv(AVFrame *sono, const ColorFloat *c, int idx)
{
    int x, fmt = sono->format, w = sono->width;
    uint8_t *lpy = sono->data[0] + idx * sono->linesize[0];
    uint8_t *lpu = sono->data[1] + idx * sono->linesize[1];
    uint8_t *lpv = sono->data[2] + idx * sono->linesize[2];

    for (x = 0; x < w; x += 2) {
        *lpy++ = lrintf(c[x].yuv.y + 16.0f);
        *lpu++ = lrintf(c[x].yuv.u + 128.0f);
        *lpv++ = lrintf(c[x].yuv.v + 128.0f);
        *lpy++ = lrintf(c[x+1].yuv.y + 16.0f);
        if (fmt == AV_PIX_FMT_YUV444P) {
            *lpu++ = lrintf(c[x+1].yuv.u + 128.0f);
            *lpv++ = lrintf(c[x+1].yuv.v + 128.0f);
        }
    }
}
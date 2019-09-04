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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int width; int* linesize; int format; int /*<<< orphan*/ ** data; } ;
typedef  int /*<<< orphan*/  ColorFloat ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 int AV_PIX_FMT_YUV420P ; 
 int AV_PIX_FMT_YUV422P ; 
 int AV_PIX_FMT_YUV444P ; 
 int /*<<< orphan*/  DRAW_BAR_WITHOUT_CHROMA (int) ; 
 int /*<<< orphan*/  DRAW_BAR_WITH_CHROMA (int) ; 

__attribute__((used)) static void draw_bar_yuv(AVFrame *out, const float *h, const float *rcp_h,
                         const ColorFloat *c, int bar_h, float bar_t)
{
    int x, y, yh, w = out->width;
    float mul, ht, rcp_bar_h = 1.0f / bar_h, rcp_bar_t = 1.0f / bar_t;
    uint8_t *vy = out->data[0], *vu = out->data[1], *vv = out->data[2];
    uint8_t *lpy, *lpu, *lpv;
    int lsy = out->linesize[0], lsu = out->linesize[1], lsv = out->linesize[2];
    int fmt = out->format;

    for (y = 0; y < bar_h; y += 2) {
        yh = (fmt == AV_PIX_FMT_YUV420P) ? y / 2 : y;
        ht = (bar_h - y) * rcp_bar_h;
        lpy = vy + y * lsy;
        lpu = vu + yh * lsu;
        lpv = vv + yh * lsv;
        if (fmt == AV_PIX_FMT_YUV444P) {
            for (x = 0; x < w; x += 2) {
                DRAW_BAR_WITH_CHROMA(x);
                DRAW_BAR_WITH_CHROMA(x+1);
            }
        } else {
            for (x = 0; x < w; x += 2) {
                DRAW_BAR_WITH_CHROMA(x);
                DRAW_BAR_WITHOUT_CHROMA(x+1);
            }
        }

        ht = (bar_h - (y+1)) * rcp_bar_h;
        lpy = vy + (y+1) * lsy;
        lpu = vu + (y+1) * lsu;
        lpv = vv + (y+1) * lsv;
        if (fmt == AV_PIX_FMT_YUV444P) {
            for (x = 0; x < w; x += 2) {
                DRAW_BAR_WITH_CHROMA(x);
                DRAW_BAR_WITH_CHROMA(x+1);
            }
        } else if (fmt == AV_PIX_FMT_YUV422P) {
            for (x = 0; x < w; x += 2) {
                DRAW_BAR_WITH_CHROMA(x);
                DRAW_BAR_WITHOUT_CHROMA(x+1);
            }
        } else {
            for (x = 0; x < w; x += 2) {
                DRAW_BAR_WITHOUT_CHROMA(x);
                DRAW_BAR_WITHOUT_CHROMA(x+1);
            }
        }
    }
}
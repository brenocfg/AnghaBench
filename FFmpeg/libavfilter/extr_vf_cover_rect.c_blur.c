#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_6__ {int* linesize; int** data; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_5__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_1__ CoverContext ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 int AV_CEIL_RSHIFT (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void blur(CoverContext *cover, AVFrame *in, int offx, int offy)
{
    int x, y, p;

    for (p=0; p<3; p++) {
        int ox = offx>>!!p;
        int oy = offy>>!!p;
        int stride = in->linesize[p];
        uint8_t *data = in->data[p] + ox + oy * stride;
        int w = AV_CEIL_RSHIFT(cover->width , !!p);
        int h = AV_CEIL_RSHIFT(cover->height, !!p);
        int iw = AV_CEIL_RSHIFT(in->width , !!p);
        int ih = AV_CEIL_RSHIFT(in->height, !!p);
        for (y = 0; y < h; y++) {
            for (x = 0; x < w; x++) {
                int c = 0;
                int s = 0;
                if (ox) {
                    int scale = 65536 / (x + 1);
                    s += data[-1 + y*stride] * scale;
                    c += scale;
                }
                if (oy) {
                    int scale = 65536 / (y + 1);
                    s += data[x - stride] * scale;
                    c += scale;
                }
                if (ox + w < iw) {
                    int scale = 65536 / (w - x);
                    s += data[w + y*stride] * scale;
                    c += scale;
                }
                if (oy + h < ih) {
                    int scale = 65536 / (h - y);
                    s += data[x + h*stride] * scale;
                    c += scale;
                }
                data[x + y*stride] = c ? (s + (c>>1)) / c : 0;
            }
        }
    }
}
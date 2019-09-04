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
struct TYPE_6__ {int /*<<< orphan*/  width; int /*<<< orphan*/  height; } ;
struct TYPE_5__ {int** data; int* linesize; } ;
typedef  TYPE_1__ AVFrame ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int C64XRES ; 
 int C64YRES ; 
 int FFMIN (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void to_meta_with_crop(AVCodecContext *avctx,
                              const AVFrame *p, int *dest)
{
    int blockx, blocky, x, y;
    int luma = 0;
    int height = FFMIN(avctx->height, C64YRES);
    int width  = FFMIN(avctx->width , C64XRES);
    uint8_t *src = p->data[0];

    for (blocky = 0; blocky < C64YRES; blocky += 8) {
        for (blockx = 0; blockx < C64XRES; blockx += 8) {
            for (y = blocky; y < blocky + 8 && y < C64YRES; y++) {
                for (x = blockx; x < blockx + 8 && x < C64XRES; x += 2) {
                    if(x < width && y < height) {
                        if (x + 1 < width) {
                            /* build average over 2 pixels */
                            luma = (src[(x + 0 + y * p->linesize[0])] +
                                    src[(x + 1 + y * p->linesize[0])]) / 2;
                        } else {
                            luma = src[(x + y * p->linesize[0])];
                        }
                        /* write blocks as linear data now so they are suitable for elbg */
                        dest[0] = luma;
                    }
                    dest++;
                }
            }
        }
    }
}
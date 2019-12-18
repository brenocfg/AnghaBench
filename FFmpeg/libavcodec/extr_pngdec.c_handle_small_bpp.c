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
struct TYPE_6__ {int** data; } ;
struct TYPE_5__ {int bits_per_pixel; scalar_t__ color_type; int height; int width; int /*<<< orphan*/  image_linesize; } ;
typedef  TYPE_1__ PNGDecContext ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 scalar_t__ PNG_COLOR_TYPE_PALETTE ; 

__attribute__((used)) static void handle_small_bpp(PNGDecContext *s, AVFrame *p)
{
    if (s->bits_per_pixel == 1 && s->color_type == PNG_COLOR_TYPE_PALETTE) {
        int i, j, k;
        uint8_t *pd = p->data[0];
        for (j = 0; j < s->height; j++) {
            i = s->width / 8;
            for (k = 7; k >= 1; k--)
                if ((s->width&7) >= k)
                    pd[8*i + k - 1] = (pd[i]>>8-k) & 1;
            for (i--; i >= 0; i--) {
                pd[8*i + 7]=  pd[i]     & 1;
                pd[8*i + 6]= (pd[i]>>1) & 1;
                pd[8*i + 5]= (pd[i]>>2) & 1;
                pd[8*i + 4]= (pd[i]>>3) & 1;
                pd[8*i + 3]= (pd[i]>>4) & 1;
                pd[8*i + 2]= (pd[i]>>5) & 1;
                pd[8*i + 1]= (pd[i]>>6) & 1;
                pd[8*i + 0]=  pd[i]>>7;
            }
            pd += s->image_linesize;
        }
    } else if (s->bits_per_pixel == 2) {
        int i, j;
        uint8_t *pd = p->data[0];
        for (j = 0; j < s->height; j++) {
            i = s->width / 4;
            if (s->color_type == PNG_COLOR_TYPE_PALETTE) {
                if ((s->width&3) >= 3) pd[4*i + 2]= (pd[i] >> 2) & 3;
                if ((s->width&3) >= 2) pd[4*i + 1]= (pd[i] >> 4) & 3;
                if ((s->width&3) >= 1) pd[4*i + 0]=  pd[i] >> 6;
                for (i--; i >= 0; i--) {
                    pd[4*i + 3]=  pd[i]     & 3;
                    pd[4*i + 2]= (pd[i]>>2) & 3;
                    pd[4*i + 1]= (pd[i]>>4) & 3;
                    pd[4*i + 0]=  pd[i]>>6;
                }
            } else {
                if ((s->width&3) >= 3) pd[4*i + 2]= ((pd[i]>>2) & 3)*0x55;
                if ((s->width&3) >= 2) pd[4*i + 1]= ((pd[i]>>4) & 3)*0x55;
                if ((s->width&3) >= 1) pd[4*i + 0]= ( pd[i]>>6     )*0x55;
                for (i--; i >= 0; i--) {
                    pd[4*i + 3]= ( pd[i]     & 3)*0x55;
                    pd[4*i + 2]= ((pd[i]>>2) & 3)*0x55;
                    pd[4*i + 1]= ((pd[i]>>4) & 3)*0x55;
                    pd[4*i + 0]= ( pd[i]>>6     )*0x55;
                }
            }
            pd += s->image_linesize;
        }
    } else if (s->bits_per_pixel == 4) {
        int i, j;
        uint8_t *pd = p->data[0];
        for (j = 0; j < s->height; j++) {
            i = s->width/2;
            if (s->color_type == PNG_COLOR_TYPE_PALETTE) {
                if (s->width&1) pd[2*i+0]= pd[i]>>4;
                for (i--; i >= 0; i--) {
                    pd[2*i + 1] = pd[i] & 15;
                    pd[2*i + 0] = pd[i] >> 4;
                }
            } else {
                if (s->width & 1) pd[2*i + 0]= (pd[i] >> 4) * 0x11;
                for (i--; i >= 0; i--) {
                    pd[2*i + 1] = (pd[i] & 15) * 0x11;
                    pd[2*i + 0] = (pd[i] >> 4) * 0x11;
                }
            }
            pd += s->image_linesize;
        }
    }
}
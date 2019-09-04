#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_4__ {int** data; int* linesize; int width; int height; } ;
struct TYPE_3__ {int bps; int /*<<< orphan*/  vsub; int /*<<< orphan*/  hsub; TYPE_2__* picref; } ;
typedef  TYPE_1__ GEQContext ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 int AV_CEIL_RSHIFT (int,int /*<<< orphan*/ ) ; 
 double av_clipf (double,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static inline double getpix(void *priv, double x, double y, int plane)
{
    int xi, yi;
    GEQContext *geq = priv;
    AVFrame *picref = geq->picref;
    const uint8_t *src = picref->data[plane];
    int linesize = picref->linesize[plane];
    const int w = (plane == 1 || plane == 2) ? AV_CEIL_RSHIFT(picref->width,  geq->hsub) : picref->width;
    const int h = (plane == 1 || plane == 2) ? AV_CEIL_RSHIFT(picref->height, geq->vsub) : picref->height;

    if (!src)
        return 0;

    xi = x = av_clipf(x, 0, w - 2);
    yi = y = av_clipf(y, 0, h - 2);

    x -= xi;
    y -= yi;

    if (geq->bps > 8) {
        const uint16_t *src16 = (const uint16_t*)src;
        linesize /= 2;

        return (1-y)*((1-x)*src16[xi +  yi    * linesize] + x*src16[xi + 1 +  yi    * linesize])
              +   y *((1-x)*src16[xi + (yi+1) * linesize] + x*src16[xi + 1 + (yi+1) * linesize]);
    } else {
        return (1-y)*((1-x)*src[xi +  yi    * linesize] + x*src[xi + 1 +  yi    * linesize])
              +   y *((1-x)*src[xi + (yi+1) * linesize] + x*src[xi + 1 + (yi+1) * linesize]);
    }
}
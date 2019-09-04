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
typedef  size_t uint16_t ;
typedef  int int64_t ;
struct TYPE_8__ {TYPE_1__* priv; } ;
struct TYPE_7__ {int* linesize; scalar_t__* data; } ;
struct TYPE_6__ {int* histogram; int depth; int* planeheight; int* planewidth; } ;
typedef  TYPE_1__ DeflickerContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static float calc_avgy16(AVFilterContext *ctx, AVFrame *in)
{
    DeflickerContext *s = ctx->priv;
    const uint16_t *src = (const uint16_t *)in->data[0];
    int64_t sum = 0;
    int y, x;

    memset(s->histogram, 0, (1 << s->depth) * sizeof(*s->histogram));

    for (y = 0; y < s->planeheight[0]; y++) {
        for (x = 0; x < s->planewidth[0]; x++) {
            s->histogram[src[x]]++;
        }
        src += in->linesize[0] / 2;
    }

    for (y = 0; y < 1 << s->depth; y++) {
        sum += s->histogram[y] * y;
    }

    return 1.0f * sum / (s->planeheight[0] * s->planewidth[0]);
}
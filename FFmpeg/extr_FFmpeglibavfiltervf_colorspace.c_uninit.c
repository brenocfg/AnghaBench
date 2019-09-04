#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  lin_lut; int /*<<< orphan*/ ** dither_scratch_base; scalar_t__ rgb_sz; int /*<<< orphan*/ * rgb; } ;
typedef  TYPE_1__ ColorSpaceContext ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uninit(AVFilterContext *ctx)
{
    ColorSpaceContext *s = ctx->priv;

    av_freep(&s->rgb[0]);
    av_freep(&s->rgb[1]);
    av_freep(&s->rgb[2]);
    s->rgb_sz = 0;
    av_freep(&s->dither_scratch_base[0][0]);
    av_freep(&s->dither_scratch_base[0][1]);
    av_freep(&s->dither_scratch_base[1][0]);
    av_freep(&s->dither_scratch_base[1][1]);
    av_freep(&s->dither_scratch_base[2][0]);
    av_freep(&s->dither_scratch_base[2][1]);

    av_freep(&s->lin_lut);
}
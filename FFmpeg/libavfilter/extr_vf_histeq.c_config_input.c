#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  format; TYPE_3__* dst; } ;
struct TYPE_5__ {int bpp; int /*<<< orphan*/  rgba_map; } ;
typedef  TYPE_1__ HisteqContext ;
typedef  int /*<<< orphan*/  AVPixFmtDescriptor ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int av_get_bits_per_pixel (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_fill_rgba_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    HisteqContext *histeq = ctx->priv;
    const AVPixFmtDescriptor *pix_desc = av_pix_fmt_desc_get(inlink->format);

    histeq->bpp = av_get_bits_per_pixel(pix_desc) / 8;
    ff_fill_rgba_map(histeq->rgba_map, inlink->format);

    return 0;
}
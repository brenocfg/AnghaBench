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
struct TYPE_6__ {int /*<<< orphan*/  w; int /*<<< orphan*/  format; TYPE_3__* dst; } ;
struct TYPE_5__ {int /*<<< orphan*/  temp; int /*<<< orphan*/ * pixsteps; int /*<<< orphan*/  nb_planes; int /*<<< orphan*/  desc; int /*<<< orphan*/  y2; int /*<<< orphan*/  x2; int /*<<< orphan*/  y1; int /*<<< orphan*/  x1; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
typedef  TYPE_1__ SwapRectContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_image_fill_max_pixsteps (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_malloc_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_pix_fmt_count_planes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    SwapRectContext *s = ctx->priv;

    if (!s->w  || !s->h  ||
        !s->x1 || !s->y1 ||
        !s->x2 || !s->y2)
        return AVERROR(EINVAL);

    s->desc = av_pix_fmt_desc_get(inlink->format);
    av_image_fill_max_pixsteps(s->pixsteps, NULL, s->desc);
    s->nb_planes = av_pix_fmt_count_planes(inlink->format);

    s->temp = av_malloc_array(inlink->w, s->pixsteps[0]);
    if (!s->temp)
        return AVERROR(ENOMEM);

    return 0;
}
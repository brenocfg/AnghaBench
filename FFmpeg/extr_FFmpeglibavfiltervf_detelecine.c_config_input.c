#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  format; int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_1__* dst; } ;
struct TYPE_10__ {int /*<<< orphan*/  log2_chroma_h; } ;
struct TYPE_9__ {int /*<<< orphan*/  nb_planes; int /*<<< orphan*/ * planeheight; int /*<<< orphan*/  stride; void** frame; void* temp; } ;
struct TYPE_8__ {TYPE_2__* priv; } ;
typedef  TYPE_2__ DetelecineContext ;
typedef  TYPE_3__ AVPixFmtDescriptor ;
typedef  TYPE_4__ AVFilterLink ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_CEIL_RSHIFT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int av_image_fill_linesizes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_pix_fmt_count_planes (int /*<<< orphan*/ ) ; 
 TYPE_3__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 void* ff_get_video_buffer (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    DetelecineContext *s = inlink->dst->priv;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);
    int ret;

    s->temp = ff_get_video_buffer(inlink, inlink->w, inlink->h);
    if (!s->temp)
        return AVERROR(ENOMEM);

    s->frame[0] = ff_get_video_buffer(inlink, inlink->w, inlink->h);
    if (!s->frame[0])
        return AVERROR(ENOMEM);

    s->frame[1] = ff_get_video_buffer(inlink, inlink->w, inlink->h);
    if (!s->frame[1])
        return AVERROR(ENOMEM);

    if ((ret = av_image_fill_linesizes(s->stride, inlink->format, inlink->w)) < 0)
        return ret;

    s->planeheight[1] = s->planeheight[2] = AV_CEIL_RSHIFT(inlink->h, desc->log2_chroma_h);
    s->planeheight[0] = s->planeheight[3] = inlink->h;

    s->nb_planes = av_pix_fmt_count_planes(inlink->format);

    return 0;
}
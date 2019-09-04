#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  format; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  linesize; int /*<<< orphan*/  data; } ;
struct TYPE_14__ {TYPE_2__* axis_frame; int /*<<< orphan*/  format; int /*<<< orphan*/  axis_h; int /*<<< orphan*/  width; int /*<<< orphan*/  ctx; int /*<<< orphan*/  font; int /*<<< orphan*/  fontfile; } ;
typedef  TYPE_1__ ShowCQTContext ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_PIX_FMT_RGBA ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_2__* alloc_frame_empty (int /*<<< orphan*/ ,int,int) ; 
 TYPE_2__* av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int /*<<< orphan*/  convert_axis_pixel_format (int /*<<< orphan*/ ) ; 
 int ff_scale_image (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int init_axis_color (TYPE_1__*,TYPE_2__*,int) ; 
 int render_default_font (TYPE_2__*) ; 
 scalar_t__ render_fontconfig (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ render_freetype (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_axis_from_font(ShowCQTContext *s)
{
    AVFrame *tmp = NULL;
    int ret = AVERROR(ENOMEM);
    int width = 1920, height = 32;
    int default_font = 0;

    if (!(tmp = alloc_frame_empty(AV_PIX_FMT_RGBA, width, height)))
        goto fail;

    if (!(s->axis_frame = av_frame_alloc()))
        goto fail;

    if (render_freetype(s, tmp, s->fontfile) < 0 &&
        render_fontconfig(s, tmp, s->font) < 0 &&
        (default_font = 1, ret = render_default_font(tmp)) < 0)
        goto fail;

    if (default_font)
        width /= 2, height /= 2;

    if ((ret = init_axis_color(s, tmp, default_font)) < 0)
        goto fail;

    if ((ret = ff_scale_image(s->axis_frame->data, s->axis_frame->linesize, s->width, s->axis_h,
                              convert_axis_pixel_format(s->format), tmp->data, tmp->linesize,
                              width, height, AV_PIX_FMT_RGBA, s->ctx)) < 0)
        goto fail;

    av_frame_free(&tmp);
    s->axis_frame->width = s->width;
    s->axis_frame->height = s->axis_h;
    s->axis_frame->format = convert_axis_pixel_format(s->format);
    return 0;

fail:
    av_frame_free(&tmp);
    av_frame_free(&s->axis_frame);
    return ret;
}
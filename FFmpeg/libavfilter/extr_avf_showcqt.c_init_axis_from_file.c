#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_6__ {int /*<<< orphan*/  format; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  linesize; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {TYPE_3__* axis_frame; int /*<<< orphan*/  format; int /*<<< orphan*/  axis_h; int /*<<< orphan*/  width; int /*<<< orphan*/  ctx; int /*<<< orphan*/  axisfile; } ;
typedef  TYPE_1__ ShowCQTContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_3__* av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (TYPE_3__**) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  convert_axis_pixel_format (int /*<<< orphan*/ ) ; 
 int ff_load_image (int /*<<< orphan*/ **,int*,int*,int*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_scale_image (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_axis_from_file(ShowCQTContext *s)
{
    uint8_t *tmp_data[4] = { NULL };
    int tmp_linesize[4];
    enum AVPixelFormat tmp_format;
    int tmp_w, tmp_h, ret;

    if ((ret = ff_load_image(tmp_data, tmp_linesize, &tmp_w, &tmp_h, &tmp_format,
                             s->axisfile, s->ctx)) < 0)
        goto error;

    ret = AVERROR(ENOMEM);
    if (!(s->axis_frame = av_frame_alloc()))
        goto error;

    if ((ret = ff_scale_image(s->axis_frame->data, s->axis_frame->linesize, s->width, s->axis_h,
                              convert_axis_pixel_format(s->format), tmp_data, tmp_linesize, tmp_w, tmp_h,
                              tmp_format, s->ctx)) < 0)
        goto error;

    s->axis_frame->width = s->width;
    s->axis_frame->height = s->axis_h;
    s->axis_frame->format = convert_axis_pixel_format(s->format);
    av_freep(tmp_data);
    return 0;

error:
    av_frame_free(&s->axis_frame);
    av_freep(tmp_data);
    return ret;
}
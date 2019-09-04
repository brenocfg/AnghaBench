#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct plane_info {int width; int height; int /*<<< orphan*/ * directions; int /*<<< orphan*/ * gradients; int /*<<< orphan*/ * tmpbuf; } ;
typedef  int /*<<< orphan*/  int8_t ;
struct TYPE_19__ {TYPE_3__** outputs; TYPE_1__* priv; } ;
struct TYPE_18__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_4__* dst; } ;
struct TYPE_17__ {int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
struct TYPE_16__ {scalar_t__ mode; int nb_planes; int filter_planes; int /*<<< orphan*/  high_u8; int /*<<< orphan*/  low_u8; struct plane_info* planes; } ;
typedef  TYPE_1__ EdgeDetectContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ MODE_COLORMIX ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 scalar_t__ av_frame_is_writable (TYPE_2__*) ; 
 int /*<<< orphan*/  av_image_copy_plane (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int const) ; 
 int /*<<< orphan*/  color_mix (int const,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  double_threshold (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int const) ; 
 int ff_filter_frame (TYPE_3__*,TYPE_2__*) ; 
 TYPE_2__* ff_get_video_buffer (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gaussian_blur (TYPE_4__*,int const,int const,int /*<<< orphan*/ *,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  non_maximum_suppression (int const,int const,int /*<<< orphan*/ *,int const,int /*<<< orphan*/ *,int const,int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  sobel (int const,int const,int /*<<< orphan*/ *,int const,int /*<<< orphan*/ *,int const,int /*<<< orphan*/ *,int const) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    EdgeDetectContext *edgedetect = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];
    int p, direct = 0;
    AVFrame *out;

    if (edgedetect->mode != MODE_COLORMIX && av_frame_is_writable(in)) {
        direct = 1;
        out = in;
    } else {
        out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
        if (!out) {
            av_frame_free(&in);
            return AVERROR(ENOMEM);
        }
        av_frame_copy_props(out, in);
    }

    for (p = 0; p < edgedetect->nb_planes; p++) {
        struct plane_info *plane = &edgedetect->planes[p];
        uint8_t  *tmpbuf     = plane->tmpbuf;
        uint16_t *gradients  = plane->gradients;
        int8_t   *directions = plane->directions;
        const int width      = plane->width;
        const int height     = plane->height;

        if (!((1 << p) & edgedetect->filter_planes)) {
            if (!direct)
                av_image_copy_plane(out->data[p], out->linesize[p],
                                    in->data[p], in->linesize[p],
                                    width, height);
            continue;
        }

        /* gaussian filter to reduce noise  */
        gaussian_blur(ctx, width, height,
                      tmpbuf,      width,
                      in->data[p], in->linesize[p]);

        /* compute the 16-bits gradients and directions for the next step */
        sobel(width, height,
              gradients, width,
              directions,width,
              tmpbuf,    width);

        /* non_maximum_suppression() will actually keep & clip what's necessary and
         * ignore the rest, so we need a clean output buffer */
        memset(tmpbuf, 0, width * height);
        non_maximum_suppression(width, height,
                                tmpbuf,    width,
                                directions,width,
                                gradients, width);

        /* keep high values, or low values surrounded by high values */
        double_threshold(edgedetect->low_u8, edgedetect->high_u8,
                         width, height,
                         out->data[p], out->linesize[p],
                         tmpbuf,       width);

        if (edgedetect->mode == MODE_COLORMIX) {
            color_mix(width, height,
                      out->data[p], out->linesize[p],
                      in->data[p], in->linesize[p]);
        }
    }

    if (!direct)
        av_frame_free(&in);
    return ff_filter_frame(outlink, out);
}
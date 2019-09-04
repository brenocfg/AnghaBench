#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_25__ {TYPE_1__* priv; TYPE_3__** outputs; } ;
struct TYPE_24__ {int w; int h; int channels; TYPE_4__* dst; } ;
struct TYPE_23__ {int width; int height; int** data; int* linesize; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  nb_samples; scalar_t__* extended_data; int /*<<< orphan*/  pts; } ;
struct TYPE_22__ {int step; int f; int bgopacity; int* color_lut; int w; float* max; double* values; int b; int h; int draw_persistent_duration; float* max_persistent; scalar_t__ orientation; scalar_t__ draw_volume; TYPE_2__* out; scalar_t__ draw_text; int /*<<< orphan*/  rms_factor; int /*<<< orphan*/  (* meter ) (float*,int /*<<< orphan*/ ,float*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ ShowVolumeContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_WN32A (int*,int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMAX (int,int const) ; 
 int VAR_VARS_NB ; 
 int VAR_VOLUME ; 
 int /*<<< orphan*/  av_channel_layout_extract_channel (int /*<<< orphan*/ ,int) ; 
 float av_clipf (float,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* av_frame_clone (TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int /*<<< orphan*/  av_frame_make_writable (TYPE_2__*) ; 
 char* av_get_channel_name (int /*<<< orphan*/ ) ; 
 int calc_max_draw (TYPE_1__*,TYPE_3__*,float) ; 
 int /*<<< orphan*/  calc_persistent_max (TYPE_1__*,float,int) ; 
 int /*<<< orphan*/  clear_picture (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  draw_max_line (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  drawtext (TYPE_2__*,int,int,char const*,int) ; 
 int ff_filter_frame (TYPE_3__*,TYPE_2__*) ; 
 TYPE_2__* ff_get_video_buffer (TYPE_3__*,int,int) ; 
 double log10 (float) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,double) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  stub1 (float*,int /*<<< orphan*/ ,float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (float*,int /*<<< orphan*/ ,float*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *insamples)
{
    AVFilterContext *ctx = inlink->dst;
    AVFilterLink *outlink = ctx->outputs[0];
    ShowVolumeContext *s = ctx->priv;
    const int step = s->step;
    int c, j, k, max_draw;
    AVFrame *out;

    if (!s->out || s->out->width  != outlink->w ||
                   s->out->height != outlink->h) {
        av_frame_free(&s->out);
        s->out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
        if (!s->out) {
            av_frame_free(&insamples);
            return AVERROR(ENOMEM);
        }
        clear_picture(s, outlink);
    }
    s->out->pts = insamples->pts;

    if ((s->f < 1.) && (s->f > 0.)) {
        for (j = 0; j < outlink->h; j++) {
            uint8_t *dst = s->out->data[0] + j * s->out->linesize[0];
            const uint32_t alpha = s->bgopacity * 255;

            for (k = 0; k < outlink->w; k++) {
                dst[k * 4 + 0] = FFMAX(dst[k * 4 + 0] * s->f, 0);
                dst[k * 4 + 1] = FFMAX(dst[k * 4 + 1] * s->f, 0);
                dst[k * 4 + 2] = FFMAX(dst[k * 4 + 2] * s->f, 0);
                dst[k * 4 + 3] = FFMAX(dst[k * 4 + 3] * s->f, alpha);
            }
        }
    } else if (s->f == 0.) {
        clear_picture(s, outlink);
    }

    if (s->orientation) { /* vertical */
        for (c = 0; c < inlink->channels; c++) {
            float *src = (float *)insamples->extended_data[c];
            uint32_t *lut = s->color_lut + s->w * c;
            float max;

            s->meter(src, insamples->nb_samples, &s->max[c], s->rms_factor);
            max = s->max[c];

            s->values[c * VAR_VARS_NB + VAR_VOLUME] = 20.0 * log10(max);
            max = av_clipf(max, 0, 1);
            max_draw = calc_max_draw(s, outlink, max);

            for (j = max_draw; j < s->w; j++) {
                uint8_t *dst = s->out->data[0] + j * s->out->linesize[0] + c * (s->b + s->h) * 4;
                for (k = 0; k < s->h; k++) {
                    AV_WN32A(&dst[k * 4], lut[s->w - j - 1]);
                    if (j & step)
                        j += step;
                }
            }

            if (s->h >= 8 && s->draw_text) {
                const char *channel_name = av_get_channel_name(av_channel_layout_extract_channel(insamples->channel_layout, c));
                if (!channel_name)
                    continue;
                drawtext(s->out, c * (s->h + s->b) + (s->h - 10) / 2, outlink->h - 35, channel_name, 1);
            }

            if (s->draw_persistent_duration > 0.) {
                calc_persistent_max(s, max, c);
                max_draw = FFMAX(0, calc_max_draw(s, outlink, s->max_persistent[c]) - 1);
                draw_max_line(s, max_draw, c);
            }
        }
    } else { /* horizontal */
        for (c = 0; c < inlink->channels; c++) {
            float *src = (float *)insamples->extended_data[c];
            uint32_t *lut = s->color_lut + s->w * c;
            float max;

            s->meter(src, insamples->nb_samples, &s->max[c], s->rms_factor);
            max = s->max[c];

            s->values[c * VAR_VARS_NB + VAR_VOLUME] = 20.0 * log10(max);
            max = av_clipf(max, 0, 1);
            max_draw = calc_max_draw(s, outlink, max);

            for (j = 0; j < s->h; j++) {
                uint8_t *dst = s->out->data[0] + (c * s->h + c * s->b + j) * s->out->linesize[0];

                for (k = 0; k < max_draw; k++) {
                    AV_WN32A(dst + k * 4, lut[k]);
                    if (k & step)
                        k += step;
                }
            }

            if (s->h >= 8 && s->draw_text) {
                const char *channel_name = av_get_channel_name(av_channel_layout_extract_channel(insamples->channel_layout, c));
                if (!channel_name)
                    continue;
                drawtext(s->out, 2, c * (s->h + s->b) + (s->h - 8) / 2, channel_name, 0);
            }

            if (s->draw_persistent_duration > 0.) {
                calc_persistent_max(s, max, c);
                max_draw = FFMAX(0, calc_max_draw(s, outlink, s->max_persistent[c]) - 1);
                draw_max_line(s, max_draw, c);
            }
        }
    }

    av_frame_free(&insamples);
    out = av_frame_clone(s->out);
    if (!out)
        return AVERROR(ENOMEM);
    av_frame_make_writable(out);

    /* draw volume level */
    for (c = 0; c < inlink->channels && s->h >= 8 && s->draw_volume; c++) {
        char buf[16];

        if (s->orientation) { /* vertical */
            snprintf(buf, sizeof(buf), "%.2f", s->values[c * VAR_VARS_NB + VAR_VOLUME]);
            drawtext(out, c * (s->h + s->b) + (s->h - 8) / 2, 2, buf, 1);
        } else { /* horizontal */
            snprintf(buf, sizeof(buf), "%.2f", s->values[c * VAR_VARS_NB + VAR_VOLUME]);
            drawtext(out, FFMAX(0, s->w - 8 * (int)strlen(buf)), c * (s->h + s->b) + (s->h - 8) / 2, buf, 0);
        }
    }

    return ff_filter_frame(outlink, out);
}
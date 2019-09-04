#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  chlayout_str ;
struct TYPE_12__ {int** data; int* linesize; } ;
struct TYPE_11__ {TYPE_2__** outputs; TYPE_2__** inputs; TYPE_1__* priv; } ;
struct TYPE_10__ {int sample_rate; int h; int w; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  channels; } ;
struct TYPE_9__ {scalar_t__ orientation; int w; int h; scalar_t__ mode; scalar_t__ color_mode; float stop; float start; int start_y; int start_x; int nb_display_channels; scalar_t__ fscale; TYPE_6__* outpicref; scalar_t__ single_pic; } ;
typedef  TYPE_1__ ShowSpectrumContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ CHANNEL ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ F_LINEAR ; 
 scalar_t__ SEPARATE ; 
 scalar_t__ VERTICAL ; 
 char* av_asprintf (char*,...) ; 
 int /*<<< orphan*/  av_clip_uint8 (float) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 int /*<<< orphan*/  av_get_channel_layout_string (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ceil (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  color_range (TYPE_1__*,int,float*,float*,float*) ; 
 int /*<<< orphan*/  drawtext (TYPE_6__*,int,int,char*,int) ; 
 int get_log_hz (int,int,int) ; 
 char* get_time (TYPE_3__*,float,int) ; 
 float log10f (float) ; 
 int /*<<< orphan*/  log2 (int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pick_color (TYPE_1__*,float,float,float,int,float*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int draw_legend(AVFilterContext *ctx, int samples)
{
    ShowSpectrumContext *s = ctx->priv;
    AVFilterLink *inlink = ctx->inputs[0];
    AVFilterLink *outlink = ctx->outputs[0];
    int ch, y, x = 0, sz = s->orientation == VERTICAL ? s->w : s->h;
    int multi = (s->mode == SEPARATE && s->color_mode == CHANNEL);
    float spp = samples / (float)sz;
    char *text;
    uint8_t *dst;
    char chlayout_str[128];

    av_get_channel_layout_string(chlayout_str, sizeof(chlayout_str), inlink->channels,
                                 inlink->channel_layout);

    text = av_asprintf("%d Hz | %s", inlink->sample_rate, chlayout_str);

    drawtext(s->outpicref, 2, outlink->h - 10, "CREATED BY LIBAVFILTER", 0);
    drawtext(s->outpicref, outlink->w - 2 - strlen(text) * 10, outlink->h - 10, text, 0);
    if (s->stop) {
        char *text = av_asprintf("Zoom: %d Hz - %d Hz", s->start, s->stop);
        drawtext(s->outpicref, outlink->w - 2 - strlen(text) * 10, 3, text, 0);
        av_freep(&text);
    }

    av_freep(&text);

    dst = s->outpicref->data[0] + (s->start_y - 1) * s->outpicref->linesize[0] + s->start_x - 1;
    for (x = 0; x < s->w + 1; x++)
        dst[x] = 200;
    dst = s->outpicref->data[0] + (s->start_y + s->h) * s->outpicref->linesize[0] + s->start_x - 1;
    for (x = 0; x < s->w + 1; x++)
        dst[x] = 200;
    for (y = 0; y < s->h + 2; y++) {
        dst = s->outpicref->data[0] + (y + s->start_y - 1) * s->outpicref->linesize[0];
        dst[s->start_x - 1] = 200;
        dst[s->start_x + s->w] = 200;
    }
    if (s->orientation == VERTICAL) {
        int h = s->mode == SEPARATE ? s->h / s->nb_display_channels : s->h;
        int hh = s->mode == SEPARATE ? -(s->h % s->nb_display_channels) + 1 : 1;
        for (ch = 0; ch < (s->mode == SEPARATE ? s->nb_display_channels : 1); ch++) {
            for (y = 0; y < h; y += 20) {
                dst = s->outpicref->data[0] + (s->start_y + h * (ch + 1) - y - hh) * s->outpicref->linesize[0];
                dst[s->start_x - 2] = 200;
                dst[s->start_x + s->w + 1] = 200;
            }
            for (y = 0; y < h; y += 40) {
                dst = s->outpicref->data[0] + (s->start_y + h * (ch + 1) - y - hh) * s->outpicref->linesize[0];
                dst[s->start_x - 3] = 200;
                dst[s->start_x + s->w + 2] = 200;
            }
            dst = s->outpicref->data[0] + (s->start_y - 2) * s->outpicref->linesize[0] + s->start_x;
            for (x = 0; x < s->w; x+=40)
                dst[x] = 200;
            dst = s->outpicref->data[0] + (s->start_y - 3) * s->outpicref->linesize[0] + s->start_x;
            for (x = 0; x < s->w; x+=80)
                dst[x] = 200;
            dst = s->outpicref->data[0] + (s->h + s->start_y + 1) * s->outpicref->linesize[0] + s->start_x;
            for (x = 0; x < s->w; x+=40) {
                dst[x] = 200;
            }
            dst = s->outpicref->data[0] + (s->h + s->start_y + 2) * s->outpicref->linesize[0] + s->start_x;
            for (x = 0; x < s->w; x+=80) {
                dst[x] = 200;
            }
            for (y = 0; y < h; y += 40) {
                float range = s->stop ? s->stop - s->start : inlink->sample_rate / 2;
                float bin = s->fscale == F_LINEAR ? y : get_log_hz(y, h, inlink->sample_rate);
                float hertz = s->start + bin * range / (float)(1 << (int)ceil(log2(h)));
                char *units;

                if (hertz == 0)
                    units = av_asprintf("DC");
                else
                    units = av_asprintf("%.2f", hertz);
                if (!units)
                    return AVERROR(ENOMEM);

                drawtext(s->outpicref, s->start_x - 8 * strlen(units) - 4, h * (ch + 1) + s->start_y - y - 4 - hh, units, 0);
                av_free(units);
            }
        }

        for (x = 0; x < s->w && s->single_pic; x+=80) {
            float seconds = x * spp / inlink->sample_rate;
            char *units = get_time(ctx, seconds, x);

            drawtext(s->outpicref, s->start_x + x - 4 * strlen(units), s->h + s->start_y + 6, units, 0);
            drawtext(s->outpicref, s->start_x + x - 4 * strlen(units), s->start_y - 12, units, 0);
            av_free(units);
        }

        drawtext(s->outpicref, outlink->w / 2 - 4 * 4, outlink->h - s->start_y / 2, "TIME", 0);
        drawtext(s->outpicref, s->start_x / 7, outlink->h / 2 - 14 * 4, "FREQUENCY (Hz)", 1);
    } else {
        int w = s->mode == SEPARATE ? s->w / s->nb_display_channels : s->w;
        for (y = 0; y < s->h; y += 20) {
            dst = s->outpicref->data[0] + (s->start_y + y) * s->outpicref->linesize[0];
            dst[s->start_x - 2] = 200;
            dst[s->start_x + s->w + 1] = 200;
        }
        for (y = 0; y < s->h; y += 40) {
            dst = s->outpicref->data[0] + (s->start_y + y) * s->outpicref->linesize[0];
            dst[s->start_x - 3] = 200;
            dst[s->start_x + s->w + 2] = 200;
        }
        for (ch = 0; ch < (s->mode == SEPARATE ? s->nb_display_channels : 1); ch++) {
            dst = s->outpicref->data[0] + (s->start_y - 2) * s->outpicref->linesize[0] + s->start_x + w * ch;
            for (x = 0; x < w; x+=40)
                dst[x] = 200;
            dst = s->outpicref->data[0] + (s->start_y - 3) * s->outpicref->linesize[0] + s->start_x + w * ch;
            for (x = 0; x < w; x+=80)
                dst[x] = 200;
            dst = s->outpicref->data[0] + (s->h + s->start_y + 1) * s->outpicref->linesize[0] + s->start_x + w * ch;
            for (x = 0; x < w; x+=40) {
                dst[x] = 200;
            }
            dst = s->outpicref->data[0] + (s->h + s->start_y + 2) * s->outpicref->linesize[0] + s->start_x + w * ch;
            for (x = 0; x < w; x+=80) {
                dst[x] = 200;
            }
            for (x = 0; x < w - 79; x += 80) {
                float range = s->stop ? s->stop - s->start : inlink->sample_rate / 2;
                float bin = s->fscale == F_LINEAR ? x : get_log_hz(x, w, inlink->sample_rate);
                float hertz = s->start + bin * range / (float)(1 << (int)ceil(log2(w)));
                char *units;

                if (hertz == 0)
                    units = av_asprintf("DC");
                else
                    units = av_asprintf("%.2f", hertz);
                if (!units)
                    return AVERROR(ENOMEM);

                drawtext(s->outpicref, s->start_x - 4 * strlen(units) + x + w * ch, s->start_y - 12, units, 0);
                drawtext(s->outpicref, s->start_x - 4 * strlen(units) + x + w * ch, s->h + s->start_y + 6, units, 0);
                av_free(units);
            }
        }
        for (y = 0; y < s->h && s->single_pic; y+=40) {
            float seconds = y * spp / inlink->sample_rate;
            char *units = get_time(ctx, seconds, x);

            drawtext(s->outpicref, s->start_x - 8 * strlen(units) - 4, s->start_y + y - 4, units, 0);
            av_free(units);
        }
        drawtext(s->outpicref, s->start_x / 7, outlink->h / 2 - 4 * 4, "TIME", 1);
        drawtext(s->outpicref, outlink->w / 2 - 14 * 4, outlink->h - s->start_y / 2, "FREQUENCY (Hz)", 0);
    }

    for (ch = 0; ch < (multi ? s->nb_display_channels : 1); ch++) {
        int h = multi ? s->h / s->nb_display_channels : s->h;

        for (y = 0; y < h; y++) {
            float out[3] = { 0., 127.5, 127.5};
            int chn;

            for (chn = 0; chn < (s->mode == SEPARATE ? 1 : s->nb_display_channels); chn++) {
                float yf, uf, vf;
                int channel = (multi) ? s->nb_display_channels - ch - 1 : chn;
                float lout[3];

                color_range(s, channel, &yf, &uf, &vf);
                pick_color(s, yf, uf, vf, y / (float)h, lout);
                out[0] += lout[0];
                out[1] += lout[1];
                out[2] += lout[2];
            }
            memset(s->outpicref->data[0]+(s->start_y + h * (ch + 1) - y - 1) * s->outpicref->linesize[0] + s->w + s->start_x + 20, av_clip_uint8(out[0]), 10);
            memset(s->outpicref->data[1]+(s->start_y + h * (ch + 1) - y - 1) * s->outpicref->linesize[1] + s->w + s->start_x + 20, av_clip_uint8(out[1]), 10);
            memset(s->outpicref->data[2]+(s->start_y + h * (ch + 1) - y - 1) * s->outpicref->linesize[2] + s->w + s->start_x + 20, av_clip_uint8(out[2]), 10);
        }

        for (y = 0; ch == 0 && y < h; y += h / 10) {
            float value = 120.f * log10f(1.f - y / (float)h);
            char *text;

            if (value < -120)
                break;
            text = av_asprintf("%.0f dB", value);
            if (!text)
                continue;
            drawtext(s->outpicref, s->w + s->start_x + 35, s->start_y + y - 5, text, 0);
            av_free(text);
        }
    }

    return 0;
}
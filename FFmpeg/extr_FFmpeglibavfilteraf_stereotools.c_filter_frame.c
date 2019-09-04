#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_1__* priv; TYPE_3__** outputs; } ;
struct TYPE_17__ {int sample_rate; TYPE_4__* dst; } ;
struct TYPE_16__ {int nb_samples; scalar_t__* data; } ;
struct TYPE_15__ {double base; int sbal; int mpan; double slev; double mlev; double balance_in; double balance_out; double level_in; double level_out; double sc_level; double delay; int length; int mute_l; int mute_r; int phase_l; int phase_r; double* buffer; int bmode_in; double inv_atan_shape; int mode; size_t pos; double phase_cos_coef; double phase_sin_coef; int bmode_out; scalar_t__ softclip; } ;
typedef  TYPE_1__ StereoToolsContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMAX (double,double const) ; 
 int FFMIN (int,double const) ; 
 double atan (double) ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 scalar_t__ av_frame_is_writable (TYPE_2__*) ; 
 int fabs (double const) ; 
 int ff_filter_frame (TYPE_3__*,TYPE_2__*) ; 
 TYPE_2__* ff_get_audio_buffer (TYPE_3__*,int) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    AVFilterLink *outlink = ctx->outputs[0];
    StereoToolsContext *s = ctx->priv;
    const double *src = (const double *)in->data[0];
    const double sb = s->base < 0 ? s->base * 0.5 : s->base;
    const double sbal = 1 + s->sbal;
    const double mpan = 1 + s->mpan;
    const double slev = s->slev;
    const double mlev = s->mlev;
    const double balance_in = s->balance_in;
    const double balance_out = s->balance_out;
    const double level_in = s->level_in;
    const double level_out = s->level_out;
    const double sc_level = s->sc_level;
    const double delay = s->delay;
    const int length = s->length;
    const int mute_l = s->mute_l;
    const int mute_r = s->mute_r;
    const int phase_l = s->phase_l;
    const int phase_r = s->phase_r;
    double *buffer = s->buffer;
    AVFrame *out;
    double *dst;
    int nbuf = inlink->sample_rate * (fabs(delay) / 1000.);
    int n;

    nbuf -= nbuf % 2;
    if (av_frame_is_writable(in)) {
        out = in;
    } else {
        out = ff_get_audio_buffer(outlink, in->nb_samples);
        if (!out) {
            av_frame_free(&in);
            return AVERROR(ENOMEM);
        }
        av_frame_copy_props(out, in);
    }
    dst = (double *)out->data[0];

    for (n = 0; n < in->nb_samples; n++, src += 2, dst += 2) {
        double L = src[0], R = src[1], l, r, m, S, gl, gr, gd;

        L *= level_in;
        R *= level_in;

        gl = 1. - FFMAX(0., balance_in);
        gr = 1. + FFMIN(0., balance_in);
        switch (s->bmode_in) {
        case 1:
            gd = gl - gr;
            gl = 1. + gd;
            gr = 1. - gd;
            break;
        case 2:
            if (balance_in < 0.) {
                gr = FFMAX(0.5, gr);
                gl = 1. / gr;
            } else if (balance_in > 0.) {
                gl = FFMAX(0.5, gl);
                gr = 1. / gl;
            }
            break;
        }
        L *= gl;
        R *= gr;

        if (s->softclip) {
            R = s->inv_atan_shape * atan(R * sc_level);
            L = s->inv_atan_shape * atan(L * sc_level);
        }

        switch (s->mode) {
        case 0:
            m = (L + R) * 0.5;
            S = (L - R) * 0.5;
            l = m * mlev * FFMIN(1., 2. - mpan) + S * slev * FFMIN(1., 2. - sbal);
            r = m * mlev * FFMIN(1., mpan)      - S * slev * FFMIN(1., sbal);
            L = l;
            R = r;
            break;
        case 1:
            l = L * FFMIN(1., 2. - sbal);
            r = R * FFMIN(1., sbal);
            L = 0.5 * (l + r) * mlev;
            R = 0.5 * (l - r) * slev;
            break;
        case 2:
            l = L * mlev * FFMIN(1., 2. - mpan) + R * slev * FFMIN(1., 2. - sbal);
            r = L * mlev * FFMIN(1., mpan)      - R * slev * FFMIN(1., sbal);
            L = l;
            R = r;
            break;
        case 3:
            R = L;
            break;
        case 4:
            L = R;
            break;
        case 5:
            L = (L + R) / 2;
            R = L;
            break;
        case 6:
            l = L;
            L = R;
            R = l;
            m = (L + R) * 0.5;
            S = (L - R) * 0.5;
            l = m * mlev * FFMIN(1., 2. - mpan) + S * slev * FFMIN(1., 2. - sbal);
            r = m * mlev * FFMIN(1., mpan)      - S * slev * FFMIN(1., sbal);
            L = l;
            R = r;
            break;
        case 7:
            l = L * mlev * FFMIN(1., 2. - mpan) + R * slev * FFMIN(1., 2. - sbal);
            L = l;
            R = l;
            break;
        case 8:
            r = L * mlev * FFMIN(1., mpan)      - R * slev * FFMIN(1., sbal);
            L = r;
            R = r;
            break;
        }

        L *= 1. - mute_l;
        R *= 1. - mute_r;

        L *= (2. * (1. - phase_l)) - 1.;
        R *= (2. * (1. - phase_r)) - 1.;

        buffer[s->pos  ] = L;
        buffer[s->pos+1] = R;

        if (delay > 0.) {
            R = buffer[(s->pos - (int)nbuf + 1 + length) % length];
        } else if (delay < 0.) {
            L = buffer[(s->pos - (int)nbuf + length)     % length];
        }

        l = L + sb * L - sb * R;
        r = R + sb * R - sb * L;

        L = l;
        R = r;

        l = L * s->phase_cos_coef - R * s->phase_sin_coef;
        r = L * s->phase_sin_coef + R * s->phase_cos_coef;

        L = l;
        R = r;

        s->pos = (s->pos + 2) % s->length;

        gl = 1. - FFMAX(0., balance_out);
        gr = 1. + FFMIN(0., balance_out);
        switch (s->bmode_out) {
        case 1:
            gd = gl - gr;
            gl = 1. + gd;
            gr = 1. - gd;
            break;
        case 2:
            if (balance_out < 0.) {
                gr = FFMAX(0.5, gr);
                gl = 1. / gr;
            } else if (balance_out > 0.) {
                gl = FFMAX(0.5, gl);
                gr = 1. / gl;
            }
            break;
        }
        L *= gl;
        R *= gr;


        L *= level_out;
        R *= level_out;

        dst[0] = L;
        dst[1] = R;
    }

    if (out != in)
        av_frame_free(&in);
    return ff_filter_frame(outlink, out);
}
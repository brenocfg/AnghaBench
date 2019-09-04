#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int i ;
struct TYPE_16__ {int nb_samples; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  format; } ;
struct TYPE_15__ {TYPE_2__* priv; } ;
struct TYPE_14__ {int sample_rate; int channels; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  format; TYPE_5__* src; } ;
struct TYPE_13__ {double attack; double decay; int /*<<< orphan*/  volume; } ;
struct TYPE_12__ {double curve_dB; char* attacks; char* decays; char* points; int nb_segments; double in_min_lin; double out_min_lin; int initial_volume; int delay_samples; int const delay; int /*<<< orphan*/  compand; TYPE_9__* delay_frame; TYPE_3__* channels; TYPE_1__* segments; scalar_t__ gain_dB; } ;
struct TYPE_11__ {int x; int y; double a; int b; } ;
typedef  TYPE_2__ CompandContext ;
typedef  TYPE_3__ ChanParam ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 double FFMIN (double,double) ; 
 double M_LN10 ; 
 double atan2 (int,int) ; 
 TYPE_9__* av_frame_alloc () ; 
 int av_frame_get_buffer (TYPE_9__*,int) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_mallocz_array (int const,int) ; 
 char* av_strtok (char*,char*,char**) ; 
 int /*<<< orphan*/  compand_delay ; 
 int /*<<< orphan*/  compand_nodelay ; 
 double cos (double) ; 
 int /*<<< orphan*/  count_items (char*,int*) ; 
 double exp (double) ; 
 scalar_t__ fabs (double) ; 
 int /*<<< orphan*/  ff_exp10 (int) ; 
 double hypot (int,int) ; 
 double sin (double) ; 
 int sscanf (char*,char*,...) ; 
 int /*<<< orphan*/  uninit (TYPE_5__*) ; 

__attribute__((used)) static int config_output(AVFilterLink *outlink)
{
    AVFilterContext *ctx  = outlink->src;
    CompandContext *s     = ctx->priv;
    const int sample_rate = outlink->sample_rate;
    double radius         = s->curve_dB * M_LN10 / 20.0;
    char *p, *saveptr     = NULL;
    const int channels    = outlink->channels;
    int nb_attacks, nb_decays, nb_points;
    int new_nb_items, num;
    int i;
    int err;


    count_items(s->attacks, &nb_attacks);
    count_items(s->decays, &nb_decays);
    count_items(s->points, &nb_points);

    if (channels <= 0) {
        av_log(ctx, AV_LOG_ERROR, "Invalid number of channels: %d\n", channels);
        return AVERROR(EINVAL);
    }

    if (nb_attacks > channels || nb_decays > channels) {
        av_log(ctx, AV_LOG_ERROR,
                "Number of attacks/decays bigger than number of channels.\n");
        return AVERROR(EINVAL);
    }

    uninit(ctx);

    s->channels = av_mallocz_array(channels, sizeof(*s->channels));
    s->nb_segments = (nb_points + 4) * 2;
    s->segments = av_mallocz_array(s->nb_segments, sizeof(*s->segments));

    if (!s->channels || !s->segments) {
        uninit(ctx);
        return AVERROR(ENOMEM);
    }

    p = s->attacks;
    for (i = 0, new_nb_items = 0; i < nb_attacks; i++) {
        char *tstr = av_strtok(p, " |", &saveptr);
        if (!tstr) {
            uninit(ctx);
            return AVERROR(EINVAL);
        }
        p = NULL;
        new_nb_items += sscanf(tstr, "%lf", &s->channels[i].attack) == 1;
        if (s->channels[i].attack < 0) {
            uninit(ctx);
            return AVERROR(EINVAL);
        }
    }
    nb_attacks = new_nb_items;

    p = s->decays;
    for (i = 0, new_nb_items = 0; i < nb_decays; i++) {
        char *tstr = av_strtok(p, " |", &saveptr);
        if (!tstr) {
            uninit(ctx);
            return AVERROR(EINVAL);
        }
        p = NULL;
        new_nb_items += sscanf(tstr, "%lf", &s->channels[i].decay) == 1;
        if (s->channels[i].decay < 0) {
            uninit(ctx);
            return AVERROR(EINVAL);
        }
    }
    nb_decays = new_nb_items;

    if (nb_attacks != nb_decays) {
        av_log(ctx, AV_LOG_ERROR,
                "Number of attacks %d differs from number of decays %d.\n",
                nb_attacks, nb_decays);
        uninit(ctx);
        return AVERROR(EINVAL);
    }

    for (i = nb_decays; i < channels; i++) {
        s->channels[i].attack = s->channels[nb_decays - 1].attack;
        s->channels[i].decay = s->channels[nb_decays - 1].decay;
    }

#define S(x) s->segments[2 * ((x) + 1)]
    p = s->points;
    for (i = 0, new_nb_items = 0; i < nb_points; i++) {
        char *tstr = av_strtok(p, " |", &saveptr);
        p = NULL;
        if (!tstr || sscanf(tstr, "%lf/%lf", &S(i).x, &S(i).y) != 2) {
            av_log(ctx, AV_LOG_ERROR,
                    "Invalid and/or missing input/output value.\n");
            uninit(ctx);
            return AVERROR(EINVAL);
        }
        if (i && S(i - 1).x > S(i).x) {
            av_log(ctx, AV_LOG_ERROR,
                    "Transfer function input values must be increasing.\n");
            uninit(ctx);
            return AVERROR(EINVAL);
        }
        S(i).y -= S(i).x;
        av_log(ctx, AV_LOG_DEBUG, "%d: x=%f y=%f\n", i, S(i).x, S(i).y);
        new_nb_items++;
    }
    num = new_nb_items;

    /* Add 0,0 if necessary */
    if (num == 0 || S(num - 1).x)
        num++;

#undef S
#define S(x) s->segments[2 * (x)]
    /* Add a tail off segment at the start */
    S(0).x = S(1).x - 2 * s->curve_dB;
    S(0).y = S(1).y;
    num++;

    /* Join adjacent colinear segments */
    for (i = 2; i < num; i++) {
        double g1 = (S(i - 1).y - S(i - 2).y) * (S(i - 0).x - S(i - 1).x);
        double g2 = (S(i - 0).y - S(i - 1).y) * (S(i - 1).x - S(i - 2).x);
        int j;

        if (fabs(g1 - g2))
            continue;
        num--;
        for (j = --i; j < num; j++)
            S(j) = S(j + 1);
    }

    for (i = 0; i < s->nb_segments; i += 2) {
        s->segments[i].y += s->gain_dB;
        s->segments[i].x *= M_LN10 / 20;
        s->segments[i].y *= M_LN10 / 20;
    }

#define L(x) s->segments[i - (x)]
    for (i = 4; i < s->nb_segments; i += 2) {
        double x, y, cx, cy, in1, in2, out1, out2, theta, len, r;

        L(4).a = 0;
        L(4).b = (L(2).y - L(4).y) / (L(2).x - L(4).x);

        L(2).a = 0;
        L(2).b = (L(0).y - L(2).y) / (L(0).x - L(2).x);

        theta = atan2(L(2).y - L(4).y, L(2).x - L(4).x);
        len = hypot(L(2).x - L(4).x, L(2).y - L(4).y);
        r = FFMIN(radius, len);
        L(3).x = L(2).x - r * cos(theta);
        L(3).y = L(2).y - r * sin(theta);

        theta = atan2(L(0).y - L(2).y, L(0).x - L(2).x);
        len = hypot(L(0).x - L(2).x, L(0).y - L(2).y);
        r = FFMIN(radius, len / 2);
        x = L(2).x + r * cos(theta);
        y = L(2).y + r * sin(theta);

        cx = (L(3).x + L(2).x + x) / 3;
        cy = (L(3).y + L(2).y + y) / 3;

        L(2).x = x;
        L(2).y = y;

        in1  = cx - L(3).x;
        out1 = cy - L(3).y;
        in2  = L(2).x - L(3).x;
        out2 = L(2).y - L(3).y;
        L(3).a = (out2 / in2 - out1 / in1) / (in2 - in1);
        L(3).b = out1 / in1 - L(3).a * in1;
    }
    L(3).x = 0;
    L(3).y = L(2).y;

    s->in_min_lin  = exp(s->segments[1].x);
    s->out_min_lin = exp(s->segments[1].y);

    for (i = 0; i < channels; i++) {
        ChanParam *cp = &s->channels[i];

        if (cp->attack > 1.0 / sample_rate)
            cp->attack = 1.0 - exp(-1.0 / (sample_rate * cp->attack));
        else
            cp->attack = 1.0;
        if (cp->decay > 1.0 / sample_rate)
            cp->decay = 1.0 - exp(-1.0 / (sample_rate * cp->decay));
        else
            cp->decay = 1.0;
        cp->volume = ff_exp10(s->initial_volume / 20);
    }

    s->delay_samples = s->delay * sample_rate;
    if (s->delay_samples <= 0) {
        s->compand = compand_nodelay;
        return 0;
    }

    s->delay_frame = av_frame_alloc();
    if (!s->delay_frame) {
        uninit(ctx);
        return AVERROR(ENOMEM);
    }

    s->delay_frame->format         = outlink->format;
    s->delay_frame->nb_samples     = s->delay_samples;
    s->delay_frame->channel_layout = outlink->channel_layout;

    err = av_frame_get_buffer(s->delay_frame, 32);
    if (err)
        return err;

    s->compand = compand_delay;
    return 0;
}
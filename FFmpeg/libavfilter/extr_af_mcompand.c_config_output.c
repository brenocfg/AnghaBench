#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {double curve_dB; int nb_segments; double gain_dB; void* segments; } ;
struct TYPE_15__ {TYPE_2__* priv; } ;
struct TYPE_14__ {int channels; double sample_rate; TYPE_4__* src; } ;
struct TYPE_13__ {char* args; int nb_bands; int delay_buf_size; TYPE_1__* bands; } ;
struct TYPE_12__ {double* attack_rate; double* decay_rate; double* volume; double topfreq; double delay; int /*<<< orphan*/  delay_buf; TYPE_6__ transfer_fn; int /*<<< orphan*/  filter; } ;
typedef  TYPE_2__ MCompandContext ;
typedef  int /*<<< orphan*/  CompandSegment ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* FFMAX (int,int) ; 
 int FFMIN (int,int) ; 
 double M_LN10 ; 
 void* av_calloc (int,int) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 char* av_strtok (char*,char*,char**) ; 
 int /*<<< orphan*/  count_items (char*,int*,char) ; 
 int crossover_setup (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 double exp (double) ; 
 int /*<<< orphan*/  ff_get_audio_buffer (TYPE_3__*,int) ; 
 int parse_points (char*,int,double,TYPE_6__*,TYPE_4__*) ; 
 double pow (double,double) ; 
 int sscanf (char*,char*,double*) ; 
 int /*<<< orphan*/  uninit (TYPE_4__*) ; 

__attribute__((used)) static int config_output(AVFilterLink *outlink)
{
    AVFilterContext *ctx  = outlink->src;
    MCompandContext *s    = ctx->priv;
    int ret, ch, i, k, new_nb_items, nb_bands;
    char *p = s->args, *saveptr = NULL;
    int max_delay_size = 0;

    count_items(s->args, &nb_bands, '|');
    s->nb_bands = FFMAX(1, nb_bands);

    s->bands = av_calloc(nb_bands, sizeof(*s->bands));
    if (!s->bands)
        return AVERROR(ENOMEM);

    for (i = 0, new_nb_items = 0; i < nb_bands; i++) {
        int nb_points, nb_attacks, nb_items = 0;
        char *tstr2, *tstr = av_strtok(p, "|", &saveptr);
        char *p2, *p3, *saveptr2 = NULL, *saveptr3 = NULL;
        double radius;

        if (!tstr) {
            uninit(ctx);
            return AVERROR(EINVAL);
        }
        p = NULL;

        p2 = tstr;
        count_items(tstr, &nb_items, ' ');
        tstr2 = av_strtok(p2, " ", &saveptr2);
        if (!tstr2) {
            av_log(ctx, AV_LOG_ERROR, "at least one attacks/decays rate is mandatory\n");
            uninit(ctx);
            return AVERROR(EINVAL);
        }
        p2 = NULL;
        p3 = tstr2;

        count_items(tstr2, &nb_attacks, ',');
        if (!nb_attacks || nb_attacks & 1) {
            av_log(ctx, AV_LOG_ERROR, "number of attacks rate plus decays rate must be even\n");
            uninit(ctx);
            return AVERROR(EINVAL);
        }

        s->bands[i].attack_rate = av_calloc(outlink->channels, sizeof(double));
        s->bands[i].decay_rate = av_calloc(outlink->channels, sizeof(double));
        s->bands[i].volume = av_calloc(outlink->channels, sizeof(double));
        for (k = 0; k < FFMIN(nb_attacks / 2, outlink->channels); k++) {
            char *tstr3 = av_strtok(p3, ",", &saveptr3);

            p3 = NULL;
            sscanf(tstr3, "%lf", &s->bands[i].attack_rate[k]);
            tstr3 = av_strtok(p3, ",", &saveptr3);
            sscanf(tstr3, "%lf", &s->bands[i].decay_rate[k]);

            if (s->bands[i].attack_rate[k] > 1.0 / outlink->sample_rate) {
                s->bands[i].attack_rate[k] = 1.0 - exp(-1.0 / (outlink->sample_rate * s->bands[i].attack_rate[k]));
            } else {
                s->bands[i].attack_rate[k] = 1.0;
            }

            if (s->bands[i].decay_rate[k] > 1.0 / outlink->sample_rate) {
                s->bands[i].decay_rate[k] = 1.0 - exp(-1.0 / (outlink->sample_rate * s->bands[i].decay_rate[k]));
            } else {
                s->bands[i].decay_rate[k] = 1.0;
            }
        }

        for (ch = k; ch < outlink->channels; ch++) {
            s->bands[i].attack_rate[ch] = s->bands[i].attack_rate[k - 1];
            s->bands[i].decay_rate[ch]  = s->bands[i].decay_rate[k - 1];
        }

        tstr2 = av_strtok(p2, " ", &saveptr2);
        if (!tstr2) {
            av_log(ctx, AV_LOG_ERROR, "transfer function curve in dB must be set\n");
            uninit(ctx);
            return AVERROR(EINVAL);
        }
        sscanf(tstr2, "%lf", &s->bands[i].transfer_fn.curve_dB);

        radius = s->bands[i].transfer_fn.curve_dB * M_LN10 / 20.0;

        tstr2 = av_strtok(p2, " ", &saveptr2);
        if (!tstr2) {
            av_log(ctx, AV_LOG_ERROR, "transfer points missing\n");
            uninit(ctx);
            return AVERROR(EINVAL);
        }

        count_items(tstr2, &nb_points, ',');
        s->bands[i].transfer_fn.nb_segments = (nb_points + 4) * 2;
        s->bands[i].transfer_fn.segments = av_calloc(s->bands[i].transfer_fn.nb_segments,
                                                     sizeof(CompandSegment));
        if (!s->bands[i].transfer_fn.segments) {
            uninit(ctx);
            return AVERROR(ENOMEM);
        }

        ret = parse_points(tstr2, nb_points, radius, &s->bands[i].transfer_fn, ctx);
        if (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "transfer points parsing failed\n");
            uninit(ctx);
            return ret;
        }

        tstr2 = av_strtok(p2, " ", &saveptr2);
        if (!tstr2) {
            av_log(ctx, AV_LOG_ERROR, "crossover_frequency is missing\n");
            uninit(ctx);
            return AVERROR(EINVAL);
        }

        new_nb_items += sscanf(tstr2, "%lf", &s->bands[i].topfreq) == 1;
        if (s->bands[i].topfreq < 0 || s->bands[i].topfreq >= outlink->sample_rate / 2) {
            av_log(ctx, AV_LOG_ERROR, "crossover_frequency: %f, should be >=0 and lower than half of sample rate: %d.\n", s->bands[i].topfreq, outlink->sample_rate / 2);
            uninit(ctx);
            return AVERROR(EINVAL);
        }

        if (s->bands[i].topfreq != 0) {
            ret = crossover_setup(outlink, &s->bands[i].filter, s->bands[i].topfreq);
            if (ret < 0) {
                uninit(ctx);
                return ret;
            }
        }

        tstr2 = av_strtok(p2, " ", &saveptr2);
        if (tstr2) {
            sscanf(tstr2, "%lf", &s->bands[i].delay);
            max_delay_size = FFMAX(max_delay_size, s->bands[i].delay * outlink->sample_rate);

            tstr2 = av_strtok(p2, " ", &saveptr2);
            if (tstr2) {
                double initial_volume;

                sscanf(tstr2, "%lf", &initial_volume);
                initial_volume = pow(10.0, initial_volume / 20);

                for (k = 0; k < outlink->channels; k++) {
                    s->bands[i].volume[k] = initial_volume;
                }

                tstr2 = av_strtok(p2, " ", &saveptr2);
                if (tstr2) {
                    sscanf(tstr2, "%lf", &s->bands[i].transfer_fn.gain_dB);
                }
            }
        }
    }
    s->nb_bands = new_nb_items;

    for (i = 0; max_delay_size > 0 && i < s->nb_bands; i++) {
        s->bands[i].delay_buf = ff_get_audio_buffer(outlink, max_delay_size);
        if (!s->bands[i].delay_buf)
            return AVERROR(ENOMEM);
    }
    s->delay_buf_size = max_delay_size;

    return 0;
}
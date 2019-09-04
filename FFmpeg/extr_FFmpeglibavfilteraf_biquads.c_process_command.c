#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ ** outputs; TYPE_1__* priv; } ;
struct TYPE_5__ {scalar_t__ filter_type; double frequency; double gain; double width; char width_type; double a0; double a1; double a2; double b0; double b1; double b2; } ;
typedef  TYPE_1__ BiquadsContext ;
typedef  int /*<<< orphan*/  AVFilterLink ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 char HERTZ ; 
 char KHERTZ ; 
 char OCTAVE ; 
 char QFACTOR ; 
 char SLOPE ; 
 scalar_t__ allpass ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ bandpass ; 
 scalar_t__ bandreject ; 
 scalar_t__ bass ; 
 scalar_t__ biquad ; 
 int config_filter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ equalizer ; 
 scalar_t__ highpass ; 
 scalar_t__ highshelf ; 
 scalar_t__ lowpass ; 
 scalar_t__ lowshelf ; 
 int sscanf (char const*,char*,...) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 scalar_t__ treble ; 

__attribute__((used)) static int process_command(AVFilterContext *ctx, const char *cmd, const char *args,
                           char *res, int res_len, int flags)
{
    BiquadsContext *s = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];

    if ((!strcmp(cmd, "frequency") || !strcmp(cmd, "f")) &&
        (s->filter_type == equalizer ||
         s->filter_type == lowshelf  ||
         s->filter_type == highshelf ||
         s->filter_type == bass      ||
         s->filter_type == treble    ||
         s->filter_type == bandpass  ||
         s->filter_type == bandreject||
         s->filter_type == lowpass   ||
         s->filter_type == highpass  ||
         s->filter_type == allpass)) {
        double freq;

        if (sscanf(args, "%lf", &freq) != 1) {
            av_log(ctx, AV_LOG_ERROR, "Invalid frequency value.\n");
            return AVERROR(EINVAL);
        }

        s->frequency = freq;
    } else if ((!strcmp(cmd, "gain") || !strcmp(cmd, "g")) &&
        (s->filter_type == equalizer ||
         s->filter_type == lowshelf  ||
         s->filter_type == highshelf ||
         s->filter_type == bass      ||
         s->filter_type == treble)) {
        double gain;

        if (sscanf(args, "%lf", &gain) != 1) {
            av_log(ctx, AV_LOG_ERROR, "Invalid gain value.\n");
            return AVERROR(EINVAL);
        }

        s->gain = gain;
    } else if ((!strcmp(cmd, "width") || !strcmp(cmd, "w")) &&
        (s->filter_type == equalizer ||
         s->filter_type == lowshelf  ||
         s->filter_type == highshelf ||
         s->filter_type == bass      ||
         s->filter_type == treble    ||
         s->filter_type == bandpass  ||
         s->filter_type == bandreject||
         s->filter_type == lowpass   ||
         s->filter_type == highpass  ||
         s->filter_type == allpass)) {
        double width;

        if (sscanf(args, "%lf", &width) != 1) {
            av_log(ctx, AV_LOG_ERROR, "Invalid width value.\n");
            return AVERROR(EINVAL);
        }

        s->width = width;
    } else if ((!strcmp(cmd, "width_type") || !strcmp(cmd, "t")) &&
        (s->filter_type == equalizer ||
         s->filter_type == lowshelf  ||
         s->filter_type == highshelf ||
         s->filter_type == bass      ||
         s->filter_type == treble    ||
         s->filter_type == bandpass  ||
         s->filter_type == bandreject||
         s->filter_type == lowpass   ||
         s->filter_type == highpass  ||
         s->filter_type == allpass)) {
        char width_type;

        if (sscanf(args, "%c", &width_type) != 1) {
            av_log(ctx, AV_LOG_ERROR, "Invalid width_type value.\n");
            return AVERROR(EINVAL);
        }

        switch (width_type) {
        case 'h': width_type = HERTZ;   break;
        case 'q': width_type = QFACTOR; break;
        case 'o': width_type = OCTAVE;  break;
        case 's': width_type = SLOPE;   break;
        case 'k': width_type = KHERTZ;  break;
        default:
            av_log(ctx, AV_LOG_ERROR, "Invalid width_type value: %c\n", width_type);
            return AVERROR(EINVAL);
        }

        s->width_type = width_type;
    } else if ((!strcmp(cmd, "a0") ||
                !strcmp(cmd, "a1") ||
                !strcmp(cmd, "a2") ||
                !strcmp(cmd, "b0") ||
                !strcmp(cmd, "b1") ||
                !strcmp(cmd, "b2")) &&
               s->filter_type == biquad) {
        double value;

        if (sscanf(args, "%lf", &value) != 1) {
            av_log(ctx, AV_LOG_ERROR, "Invalid biquad value.\n");
            return AVERROR(EINVAL);
        }

        if (!strcmp(cmd, "a0"))
            s->a0 = value;
        else if (!strcmp(cmd, "a1"))
            s->a1 = value;
        else if (!strcmp(cmd, "a2"))
            s->a2 = value;
        else if (!strcmp(cmd, "b0"))
            s->b0 = value;
        else if (!strcmp(cmd, "b1"))
            s->b1 = value;
        else if (!strcmp(cmd, "b2"))
            s->b2 = value;
    }

    return config_filter(outlink, 0);
}
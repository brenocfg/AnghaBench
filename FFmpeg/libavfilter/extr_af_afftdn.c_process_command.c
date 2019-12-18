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
struct TYPE_6__ {TYPE_1__* priv; } ;
struct TYPE_5__ {int sample_noise_start; int sample_noise_end; int /*<<< orphan*/  output_mode; void* noise_floor; void* noise_reduction; } ;
typedef  TYPE_1__ AudioFFTDeNoiseContext ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  IN_MODE ; 
 int /*<<< orphan*/  NOISE_MODE ; 
 int /*<<< orphan*/  OUT_MODE ; 
 void* av_clipf (float,int,int) ; 
 int av_sscanf (char const*,char*,float*) ; 
 int /*<<< orphan*/  set_parameters (TYPE_1__*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int process_command(AVFilterContext *ctx, const char *cmd, const char *args,
                           char *res, int res_len, int flags)
{
    AudioFFTDeNoiseContext *s = ctx->priv;
    int need_reset = 0;

    if (!strcmp(cmd, "sample_noise") ||
        !strcmp(cmd, "sn")) {
        if (!strcmp(args, "start")) {
            s->sample_noise_start = 1;
            s->sample_noise_end = 0;
        } else if (!strcmp(args, "end") ||
                   !strcmp(args, "stop")) {
            s->sample_noise_start = 0;
            s->sample_noise_end = 1;
        }
    } else if (!strcmp(cmd, "nr") ||
               !strcmp(cmd, "noise_reduction")) {
        float nr;

        if (av_sscanf(args, "%f", &nr) == 1) {
            s->noise_reduction = av_clipf(nr, 0.01, 97);
            need_reset = 1;
        }
    } else if (!strcmp(cmd, "nf") ||
               !strcmp(cmd, "noise_floor")) {
        float nf;

        if (av_sscanf(args, "%f", &nf) == 1) {
            s->noise_floor = av_clipf(nf, -80, -20);
            need_reset = 1;
        }
    } else if (!strcmp(cmd, "output_mode") ||
               !strcmp(cmd, "om")) {
        if (!strcmp(args, "i")) {
            s->output_mode = IN_MODE;
        } else if (!strcmp(args, "o")) {
            s->output_mode = OUT_MODE;
        } else if (!strcmp(args, "n")) {
            s->output_mode = NOISE_MODE;
        }
    }

    if (need_reset)
        set_parameters(s);

    return 0;
}
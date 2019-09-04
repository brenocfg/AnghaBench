#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int window; double tempo; scalar_t__* origin; } ;
struct TYPE_9__ {TYPE_3__* priv; } ;
struct TYPE_8__ {scalar_t__* position; } ;
typedef  TYPE_1__ AudioFragment ;
typedef  TYPE_2__ AVFilterContext ;
typedef  TYPE_3__ ATempoContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 double YAE_ATEMPO_MAX ; 
 double YAE_ATEMPO_MIN ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 double av_strtod (char const*,char**) ; 
 TYPE_1__* yae_prev_frag (TYPE_3__*) ; 

__attribute__((used)) static int yae_set_tempo(AVFilterContext *ctx, const char *arg_tempo)
{
    const AudioFragment *prev;
    ATempoContext *atempo = ctx->priv;
    char   *tail = NULL;
    double tempo = av_strtod(arg_tempo, &tail);

    if (tail && *tail) {
        av_log(ctx, AV_LOG_ERROR, "Invalid tempo value '%s'\n", arg_tempo);
        return AVERROR(EINVAL);
    }

    if (tempo < YAE_ATEMPO_MIN || tempo > YAE_ATEMPO_MAX) {
        av_log(ctx, AV_LOG_ERROR, "Tempo value %f exceeds [%f, %f] range\n",
               tempo, YAE_ATEMPO_MIN, YAE_ATEMPO_MAX);
        return AVERROR(EINVAL);
    }

    prev = yae_prev_frag(atempo);
    atempo->origin[0] = prev->position[0] + atempo->window / 2;
    atempo->origin[1] = prev->position[1] + atempo->window / 2;
    atempo->tempo = tempo;
    return 0;
}
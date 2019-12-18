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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
typedef  int int64_t ;
struct TYPE_6__ {TYPE_1__* priv; } ;
struct TYPE_5__ {double* var_values; } ;
typedef  TYPE_1__ DrawTextContext ;
typedef  TYPE_2__ AVFilterContext ;
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 double AV_TIME_BASE ; 
 int /*<<< orphan*/  EINVAL ; 
 size_t VAR_T ; 
 int /*<<< orphan*/  av_bprint_strftime (int /*<<< orphan*/ *,char const*,struct tm*) ; 
 int /*<<< orphan*/  av_bprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,char const*) ; 
 int av_parse_time (int*,char*,int) ; 
 int /*<<< orphan*/  gmtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 scalar_t__ isnan (double) ; 
 int llrint (double) ; 
 int /*<<< orphan*/  localtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int func_pts(AVFilterContext *ctx, AVBPrint *bp,
                    char *fct, unsigned argc, char **argv, int tag)
{
    DrawTextContext *s = ctx->priv;
    const char *fmt;
    double pts = s->var_values[VAR_T];
    int ret;

    fmt = argc >= 1 ? argv[0] : "flt";
    if (argc >= 2) {
        int64_t delta;
        if ((ret = av_parse_time(&delta, argv[1], 1)) < 0) {
            av_log(ctx, AV_LOG_ERROR, "Invalid delta '%s'\n", argv[1]);
            return ret;
        }
        pts += (double)delta / AV_TIME_BASE;
    }
    if (!strcmp(fmt, "flt")) {
        av_bprintf(bp, "%.6f", pts);
    } else if (!strcmp(fmt, "hms")) {
        if (isnan(pts)) {
            av_bprintf(bp, " ??:??:??.???");
        } else {
            int64_t ms = llrint(pts * 1000);
            char sign = ' ';
            if (ms < 0) {
                sign = '-';
                ms = -ms;
            }
            if (argc >= 3) {
                if (!strcmp(argv[2], "24HH")) {
                    ms %= 24 * 60 * 60 * 1000;
                } else {
                    av_log(ctx, AV_LOG_ERROR, "Invalid argument '%s'\n", argv[2]);
                    return AVERROR(EINVAL);
                }
            }
            av_bprintf(bp, "%c%02d:%02d:%02d.%03d", sign,
                       (int)(ms / (60 * 60 * 1000)),
                       (int)(ms / (60 * 1000)) % 60,
                       (int)(ms / 1000) % 60,
                       (int)(ms % 1000));
        }
    } else if (!strcmp(fmt, "localtime") ||
               !strcmp(fmt, "gmtime")) {
        struct tm tm;
        time_t ms = (time_t)pts;
        const char *timefmt = argc >= 3 ? argv[2] : "%Y-%m-%d %H:%M:%S";
        if (!strcmp(fmt, "localtime"))
            localtime_r(&ms, &tm);
        else
            gmtime_r(&ms, &tm);
        av_bprint_strftime(bp, timefmt, &tm);
    } else {
        av_log(ctx, AV_LOG_ERROR, "Invalid format '%s'\n", fmt);
        return AVERROR(EINVAL);
    }
    return 0;
}
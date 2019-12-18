#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int index; scalar_t__ start_ts; scalar_t__ end_ts; int /*<<< orphan*/  nb_commands; int /*<<< orphan*/  commands; } ;
typedef  TYPE_1__ Interval ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  DELIMS ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ INT64_MAX ; 
 int /*<<< orphan*/  SPACES ; 
 int /*<<< orphan*/  av_free (char*) ; 
 char* av_get_token (char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,...) ; 
 int av_parse_time (scalar_t__*,char*,int) ; 
 char* av_strtok (char*,char*,char**) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int parse_commands (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char const**,void*) ; 
 int /*<<< orphan*/  strspn (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_interval(Interval *interval, int interval_count,
                          const char **buf, void *log_ctx)
{
    char *intervalstr;
    int ret;

    *buf += strspn(*buf, SPACES);
    if (!**buf)
        return 0;

    /* reset data */
    memset(interval, 0, sizeof(Interval));
    interval->index = interval_count;

    /* format: INTERVAL COMMANDS */

    /* parse interval */
    intervalstr = av_get_token(buf, DELIMS);
    if (intervalstr && intervalstr[0]) {
        char *start, *end;

        start = av_strtok(intervalstr, "-", &end);
        if (!start) {
            ret = AVERROR(EINVAL);
            av_log(log_ctx, AV_LOG_ERROR,
                   "Invalid interval specification '%s' in interval #%d\n",
                   intervalstr, interval_count);
            goto end;
        }
        if ((ret = av_parse_time(&interval->start_ts, start, 1)) < 0) {
            av_log(log_ctx, AV_LOG_ERROR,
                   "Invalid start time specification '%s' in interval #%d\n",
                   start, interval_count);
            goto end;
        }

        if (end) {
            if ((ret = av_parse_time(&interval->end_ts, end, 1)) < 0) {
                av_log(log_ctx, AV_LOG_ERROR,
                       "Invalid end time specification '%s' in interval #%d\n",
                       end, interval_count);
                goto end;
            }
        } else {
            interval->end_ts = INT64_MAX;
        }
        if (interval->end_ts < interval->start_ts) {
            av_log(log_ctx, AV_LOG_ERROR,
                   "Invalid end time '%s' in interval #%d: "
                   "cannot be lesser than start time '%s'\n",
                   end, interval_count, start);
            ret = AVERROR(EINVAL);
            goto end;
        }
    } else {
        av_log(log_ctx, AV_LOG_ERROR,
               "No interval specified for interval #%d\n", interval_count);
        ret = AVERROR(EINVAL);
        goto end;
    }

    /* parse commands */
    ret = parse_commands(&interval->commands, &interval->nb_commands,
                         interval_count, buf, log_ctx);

end:
    av_free(intervalstr);
    return ret;
}
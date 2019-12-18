#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  long long int64_t ;
struct TYPE_3__ {int has_start; int start_is_offset; long long start; int has_end; int end_is_offset; int duration_frames; long long end; } ;
typedef  TYPE_1__ ReadInterval ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int av_parse_time (long long*,char*,int) ; 
 char* av_strdup (char const*) ; 
 char* strchr (char*,char) ; 
 long long strtoll (char*,char**,int) ; 

__attribute__((used)) static int parse_read_interval(const char *interval_spec,
                               ReadInterval *interval)
{
    int ret = 0;
    char *next, *p, *spec = av_strdup(interval_spec);
    if (!spec)
        return AVERROR(ENOMEM);

    if (!*spec) {
        av_log(NULL, AV_LOG_ERROR, "Invalid empty interval specification\n");
        ret = AVERROR(EINVAL);
        goto end;
    }

    p = spec;
    next = strchr(spec, '%');
    if (next)
        *next++ = 0;

    /* parse first part */
    if (*p) {
        interval->has_start = 1;

        if (*p == '+') {
            interval->start_is_offset = 1;
            p++;
        } else {
            interval->start_is_offset = 0;
        }

        ret = av_parse_time(&interval->start, p, 1);
        if (ret < 0) {
            av_log(NULL, AV_LOG_ERROR, "Invalid interval start specification '%s'\n", p);
            goto end;
        }
    } else {
        interval->has_start = 0;
    }

    /* parse second part */
    p = next;
    if (p && *p) {
        int64_t us;
        interval->has_end = 1;

        if (*p == '+') {
            interval->end_is_offset = 1;
            p++;
        } else {
            interval->end_is_offset = 0;
        }

        if (interval->end_is_offset && *p == '#') {
            long long int lli;
            char *tail;
            interval->duration_frames = 1;
            p++;
            lli = strtoll(p, &tail, 10);
            if (*tail || lli < 0) {
                av_log(NULL, AV_LOG_ERROR,
                       "Invalid or negative value '%s' for duration number of frames\n", p);
                goto end;
            }
            interval->end = lli;
        } else {
            interval->duration_frames = 0;
            ret = av_parse_time(&us, p, 1);
            if (ret < 0) {
                av_log(NULL, AV_LOG_ERROR, "Invalid interval end/duration specification '%s'\n", p);
                goto end;
            }
            interval->end = us;
        }
    } else {
        interval->has_end = 0;
    }

end:
    av_free(spec);
    return ret;
}
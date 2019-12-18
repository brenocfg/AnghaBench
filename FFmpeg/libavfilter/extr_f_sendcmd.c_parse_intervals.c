#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Interval ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMAX (int,int) ; 
 int /*<<< orphan*/  SPACES ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * av_realloc_f (int /*<<< orphan*/ *,int,int) ; 
 int parse_interval (int /*<<< orphan*/ *,int,char const**,void*) ; 
 int /*<<< orphan*/  skip_comments (char const**) ; 
 int /*<<< orphan*/  strspn (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_intervals(Interval **intervals, int *nb_intervals,
                           const char *buf, void *log_ctx)
{
    int interval_count = 0;
    int ret, n = 0;

    *intervals = NULL;
    *nb_intervals = 0;

    if (!buf)
        return 0;

    while (1) {
        Interval interval;

        skip_comments(&buf);
        if (!(*buf))
            break;

        if ((ret = parse_interval(&interval, interval_count, &buf, log_ctx)) < 0)
            return ret;

        buf += strspn(buf, SPACES);
        if (*buf) {
            if (*buf != ';') {
                av_log(log_ctx, AV_LOG_ERROR,
                       "Missing terminator or extraneous data found at the end of interval #%d\n",
                       interval_count);
                return AVERROR(EINVAL);
            }
            buf++; /* skip ';' */
        }
        interval_count++;

        /* (re)allocate commands array if required */
        if (*nb_intervals == n) {
            n = FFMAX(16, 2*n); /* first allocation = 16, or double the number */
            *intervals = av_realloc_f(*intervals, n, 2*sizeof(Interval));
            if (!*intervals) {
                av_log(log_ctx, AV_LOG_ERROR,
                       "Could not (re)allocate intervals array\n");
                return AVERROR(ENOMEM);
            }
        }

        (*intervals)[(*nb_intervals)++] = interval;
    }

    return 0;
}
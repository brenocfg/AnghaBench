#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int id; } ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* av_malloc_array (int,int) ; 
 char* av_strdup (char const*) ; 
 int /*<<< orphan*/  log_read_interval (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int parse_read_interval (char*,TYPE_1__*) ; 
 TYPE_1__* read_intervals ; 
 int read_intervals_nb ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int parse_read_intervals(const char *intervals_spec)
{
    int ret, n, i;
    char *p, *spec = av_strdup(intervals_spec);
    if (!spec)
        return AVERROR(ENOMEM);

    /* preparse specification, get number of intervals */
    for (n = 0, p = spec; *p; p++)
        if (*p == ',')
            n++;
    n++;

    read_intervals = av_malloc_array(n, sizeof(*read_intervals));
    if (!read_intervals) {
        ret = AVERROR(ENOMEM);
        goto end;
    }
    read_intervals_nb = n;

    /* parse intervals */
    p = spec;
    for (i = 0; p; i++) {
        char *next;

        av_assert0(i < read_intervals_nb);
        next = strchr(p, ',');
        if (next)
            *next++ = 0;

        read_intervals[i].id = i;
        ret = parse_read_interval(p, &read_intervals[i]);
        if (ret < 0) {
            av_log(NULL, AV_LOG_ERROR, "Error parsing read interval #%d '%s'\n",
                   i, p);
            goto end;
        }
        av_log(NULL, AV_LOG_VERBOSE, "Parsed log interval ");
        log_read_interval(&read_intervals[i], NULL, AV_LOG_VERBOSE);
        p = next;
    }
    av_assert0(i == read_intervals_nb);

end:
    av_free(spec);
    return ret;
}
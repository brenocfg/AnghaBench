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
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FAIL (int) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__* av_malloc_array (int,int) ; 
 int av_parse_time (scalar_t__*,char*,int) ; 
 char* av_strdup (char const*) ; 
 char* av_strtok (char*,char*,char**) ; 

__attribute__((used)) static int parse_times(void *log_ctx, int64_t **times, int *nb_times,
                       const char *times_str)
{
    char *p;
    int i, ret = 0;
    char *times_str1 = av_strdup(times_str);
    char *saveptr = NULL;

    if (!times_str1)
        return AVERROR(ENOMEM);

#define FAIL(err) ret = err; goto end

    *nb_times = 1;
    for (p = times_str1; *p; p++)
        if (*p == ',')
            (*nb_times)++;

    *times = av_malloc_array(*nb_times, sizeof(**times));
    if (!*times) {
        av_log(log_ctx, AV_LOG_ERROR, "Could not allocate forced times array\n");
        FAIL(AVERROR(ENOMEM));
    }

    p = times_str1;
    for (i = 0; i < *nb_times; i++) {
        int64_t t;
        char *tstr = av_strtok(p, ",", &saveptr);
        p = NULL;

        if (!tstr || !tstr[0]) {
            av_log(log_ctx, AV_LOG_ERROR, "Empty time specification in times list %s\n",
                   times_str);
            FAIL(AVERROR(EINVAL));
        }

        ret = av_parse_time(&t, tstr, 1);
        if (ret < 0) {
            av_log(log_ctx, AV_LOG_ERROR,
                   "Invalid time duration specification '%s' in times list %s\n", tstr, times_str);
            FAIL(AVERROR(EINVAL));
        }
        (*times)[i] = t;

        /* check on monotonicity */
        if (i && (*times)[i-1] > (*times)[i]) {
            av_log(log_ctx, AV_LOG_ERROR,
                   "Specified time %f is greater than the following time %f\n",
                   (float)((*times)[i])/1000000, (float)((*times)[i-1])/1000000);
            FAIL(AVERROR(EINVAL));
        }
    }

end:
    av_free(times_str1);
    return ret;
}
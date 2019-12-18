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

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FAIL (int) ; 
 long INT_MAX ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,...) ; 
 int* av_malloc_array (int,int) ; 
 char* av_strdup (char const*) ; 
 char* av_strtok (char*,char*,char**) ; 
 long strtol (char*,char**,int) ; 

__attribute__((used)) static int parse_frames(void *log_ctx, int **frames, int *nb_frames,
                        const char *frames_str)
{
    char *p;
    int i, ret = 0;
    char *frames_str1 = av_strdup(frames_str);
    char *saveptr = NULL;

    if (!frames_str1)
        return AVERROR(ENOMEM);

#define FAIL(err) ret = err; goto end

    *nb_frames = 1;
    for (p = frames_str1; *p; p++)
        if (*p == ',')
            (*nb_frames)++;

    *frames = av_malloc_array(*nb_frames, sizeof(**frames));
    if (!*frames) {
        av_log(log_ctx, AV_LOG_ERROR, "Could not allocate forced frames array\n");
        FAIL(AVERROR(ENOMEM));
    }

    p = frames_str1;
    for (i = 0; i < *nb_frames; i++) {
        long int f;
        char *tailptr;
        char *fstr = av_strtok(p, ",", &saveptr);

        p = NULL;
        if (!fstr) {
            av_log(log_ctx, AV_LOG_ERROR, "Empty frame specification in frame list %s\n",
                   frames_str);
            FAIL(AVERROR(EINVAL));
        }
        f = strtol(fstr, &tailptr, 10);
        if (*tailptr || f <= 0 || f >= INT_MAX) {
            av_log(log_ctx, AV_LOG_ERROR,
                   "Invalid argument '%s', must be a positive integer <= INT64_MAX\n",
                   fstr);
            FAIL(AVERROR(EINVAL));
        }
        (*frames)[i] = f;

        /* check on monotonicity */
        if (i && (*frames)[i-1] > (*frames)[i]) {
            av_log(log_ctx, AV_LOG_ERROR,
                   "Specified frame %d is greater than the following frame %d\n",
                   (*frames)[i], (*frames)[i-1]);
            FAIL(AVERROR(EINVAL));
        }
    }

end:
    av_free(frames_str1);
    return ret;
}
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
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 char* av_strdup (char*) ; 
 char* av_strtok (char*,char*,char**) ; 
 int sscanf (char*,char const*,double*,double*) ; 

__attribute__((used)) static int read_zp_coefficients(AVFilterContext *ctx, char *item_str, int nb_items, double *dst, const char *format)
{
    char *p, *arg, *old_str, *saveptr = NULL;
    int i;

    p = old_str = av_strdup(item_str);
    if (!p)
        return AVERROR(ENOMEM);
    for (i = 0; i < nb_items; i++) {
        if (!(arg = av_strtok(p, " ", &saveptr)))
            break;

        p = NULL;
        if (sscanf(arg, format, &dst[i*2], &dst[i*2+1]) != 2) {
            av_log(ctx, AV_LOG_ERROR, "Invalid coefficients supplied: %s\n", arg);
            av_freep(&old_str);
            return AVERROR(EINVAL);
        }
    }

    av_freep(&old_str);

    return 0;
}
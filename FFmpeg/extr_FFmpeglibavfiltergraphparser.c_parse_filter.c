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
typedef  int /*<<< orphan*/  AVFilterGraph ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_free (char*) ; 
 char* av_get_token (char const**,char*) ; 
 int create_filter (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int,char*,char*,void*) ; 

__attribute__((used)) static int parse_filter(AVFilterContext **filt_ctx, const char **buf, AVFilterGraph *graph,
                        int index, void *log_ctx)
{
    char *opts = NULL;
    char *name = av_get_token(buf, "=,;[");
    int ret;

    if (**buf == '=') {
        (*buf)++;
        opts = av_get_token(buf, "[],;");
    }

    ret = create_filter(filt_ctx, graph, index, name, opts, log_ctx);
    av_free(name);
    av_free(opts);
    return ret;
}
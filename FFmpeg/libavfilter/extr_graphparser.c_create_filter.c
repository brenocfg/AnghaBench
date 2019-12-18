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
typedef  int /*<<< orphan*/  name2 ;
struct TYPE_4__ {char* scale_sws_opts; } ;
typedef  TYPE_1__ AVFilterGraph ;
typedef  int /*<<< orphan*/  AVFilterContext ;
typedef  int /*<<< orphan*/  AVFilter ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 char* av_asprintf (char*,char const*,char*) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_strlcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  avfilter_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * avfilter_get_by_name (char const*) ; 
 int /*<<< orphan*/ * avfilter_graph_alloc_filter (TYPE_1__*,int /*<<< orphan*/  const*,char const*) ; 
 int avfilter_init_str (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,int) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strstr (char const*,char*) ; 

__attribute__((used)) static int create_filter(AVFilterContext **filt_ctx, AVFilterGraph *ctx, int index,
                         const char *name, const char *args, void *log_ctx)
{
    const AVFilter *filt;
    char name2[30];
    const char *inst_name = NULL, *filt_name = NULL;
    char *tmp_args = NULL;
    int ret, k;

    av_strlcpy(name2, name, sizeof(name2));

    for (k = 0; name2[k]; k++) {
        if (name2[k] == '@' && name[k+1]) {
            name2[k] = 0;
            inst_name = name;
            filt_name = name2;
            break;
        }
    }

    if (!inst_name) {
        snprintf(name2, sizeof(name2), "Parsed_%s_%d", name, index);
        inst_name = name2;
        filt_name = name;
    }

    filt = avfilter_get_by_name(filt_name);

    if (!filt) {
        av_log(log_ctx, AV_LOG_ERROR,
               "No such filter: '%s'\n", filt_name);
        return AVERROR(EINVAL);
    }

    *filt_ctx = avfilter_graph_alloc_filter(ctx, filt, inst_name);
    if (!*filt_ctx) {
        av_log(log_ctx, AV_LOG_ERROR,
               "Error creating filter '%s'\n", filt_name);
        return AVERROR(ENOMEM);
    }

    if (!strcmp(filt_name, "scale") && (!args || !strstr(args, "flags")) &&
        ctx->scale_sws_opts) {
        if (args) {
            tmp_args = av_asprintf("%s:%s",
                    args, ctx->scale_sws_opts);
            if (!tmp_args)
                return AVERROR(ENOMEM);
            args = tmp_args;
        } else
            args = ctx->scale_sws_opts;
    }

    ret = avfilter_init_str(*filt_ctx, args);
    if (ret < 0) {
        av_log(log_ctx, AV_LOG_ERROR,
               "Error initializing filter '%s'", filt_name);
        if (args)
            av_log(log_ctx, AV_LOG_ERROR, " with args '%s'", args);
        av_log(log_ctx, AV_LOG_ERROR, "\n");
        avfilter_free(*filt_ctx);
        *filt_ctx = NULL;
    }

    av_free(tmp_args);
    return ret;
}
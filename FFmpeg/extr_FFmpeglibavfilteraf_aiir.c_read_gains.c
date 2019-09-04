#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* priv; } ;
struct TYPE_7__ {TYPE_1__* iir; } ;
struct TYPE_6__ {int /*<<< orphan*/  g; } ;
typedef  TYPE_2__ AudioIIRContext ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,char*) ; 
 char* av_strdup (char*) ; 
 char* av_strtok (char*,char*,char**) ; 
 int sscanf (char*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_gains(AVFilterContext *ctx, char *item_str, int nb_items)
{
    AudioIIRContext *s = ctx->priv;
    char *p, *arg, *old_str, *prev_arg = NULL, *saveptr = NULL;
    int i;

    p = old_str = av_strdup(item_str);
    if (!p)
        return AVERROR(ENOMEM);
    for (i = 0; i < nb_items; i++) {
        if (!(arg = av_strtok(p, "|", &saveptr)))
            arg = prev_arg;

        if (!arg) {
            av_freep(&old_str);
            return AVERROR(EINVAL);
        }

        p = NULL;
        if (sscanf(arg, "%lf", &s->iir[i].g) != 1) {
            av_log(ctx, AV_LOG_ERROR, "Invalid gains supplied: %s\n", arg);
            av_freep(&old_str);
            return AVERROR(EINVAL);
        }

        prev_arg = arg;
    }

    av_freep(&old_str);

    return 0;
}
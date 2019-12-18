#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  local_res ;
struct TYPE_8__ {TYPE_1__* filter; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int (* process_command ) (TYPE_2__*,char const*,char const*,char*,int,int) ;int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  av_strlcatf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int set_enable_expr (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int stub1 (TYPE_2__*,char const*,char const*,char*,int,int) ; 

int avfilter_process_command(AVFilterContext *filter, const char *cmd, const char *arg, char *res, int res_len, int flags)
{
    if(!strcmp(cmd, "ping")){
        char local_res[256] = {0};

        if (!res) {
            res = local_res;
            res_len = sizeof(local_res);
        }
        av_strlcatf(res, res_len, "pong from:%s %s\n", filter->filter->name, filter->name);
        if (res == local_res)
            av_log(filter, AV_LOG_INFO, "%s", res);
        return 0;
    }else if(!strcmp(cmd, "enable")) {
        return set_enable_expr(filter, arg);
    }else if(filter->filter->process_command) {
        return filter->filter->process_command(filter, cmd, arg, res, res_len, flags);
    }
    return AVERROR(ENOSYS);
}
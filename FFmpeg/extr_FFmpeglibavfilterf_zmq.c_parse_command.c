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
struct TYPE_3__ {void* arg; int /*<<< orphan*/ * command; int /*<<< orphan*/ * target; } ;
typedef  TYPE_1__ Command ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  SPACES ; 
 void* av_get_token (char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static int parse_command(Command *cmd, const char *command_str, void *log_ctx)
{
    const char **buf = &command_str;

    cmd->target = av_get_token(buf, SPACES);
    if (!cmd->target || !cmd->target[0]) {
        av_log(log_ctx, AV_LOG_ERROR,
               "No target specified in command '%s'\n", command_str);
        return AVERROR(EINVAL);
    }

    cmd->command = av_get_token(buf, SPACES);
    if (!cmd->command || !cmd->command[0]) {
        av_log(log_ctx, AV_LOG_ERROR,
               "No command specified in command '%s'\n", command_str);
        return AVERROR(EINVAL);
    }

    cmd->arg = av_get_token(buf, SPACES);
    return 0;
}
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
typedef  int /*<<< orphan*/  redisContext ;

/* Variables and functions */
 int REDIS_ERR ; 
 int /*<<< orphan*/  REDIS_ERR_OOM ; 
 scalar_t__ REDIS_OK ; 
 scalar_t__ __redisAppendCommand (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  __redisSetError (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int redisFormatCommandArgv (char**,int,char const**,size_t const*) ; 

int redisAppendCommandArgv(redisContext *c, int argc, const char **argv, const size_t *argvlen) {
    char *cmd;
    int len;

    len = redisFormatCommandArgv(&cmd,argc,argv,argvlen);
    if (len == -1) {
        __redisSetError(c,REDIS_ERR_OOM,"Out of memory");
        return REDIS_ERR;
    }

    if (__redisAppendCommand(c,cmd,len) != REDIS_OK) {
        free(cmd);
        return REDIS_ERR;
    }

    free(cmd);
    return REDIS_OK;
}
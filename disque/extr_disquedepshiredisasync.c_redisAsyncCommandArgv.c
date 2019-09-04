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
typedef  int /*<<< orphan*/  redisCallbackFn ;
typedef  int /*<<< orphan*/  redisAsyncContext ;

/* Variables and functions */
 int __redisAsyncCommand (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int redisFormatCommandArgv (char**,int,char const**,size_t const*) ; 

int redisAsyncCommandArgv(redisAsyncContext *ac, redisCallbackFn *fn, void *privdata, int argc, const char **argv, const size_t *argvlen) {
    char *cmd;
    int len;
    int status;
    len = redisFormatCommandArgv(&cmd,argc,argv,argvlen);
    status = __redisAsyncCommand(ac,fn,privdata,cmd,len);
    free(cmd);
    return status;
}
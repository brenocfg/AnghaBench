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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  redisContext ;

/* Variables and functions */
 int REDIS_ERR ; 
 int /*<<< orphan*/  REDIS_ERR_OOM ; 
 scalar_t__ REDIS_OK ; 
 scalar_t__ __redisAppendCommand (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  __redisSetError (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int redisvFormatCommand (char**,char const*,int /*<<< orphan*/ ) ; 

int redisvAppendCommand(redisContext *c, const char *format, va_list ap) {
    char *cmd;
    int len;

    len = redisvFormatCommand(&cmd,format,ap);
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
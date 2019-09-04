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
 scalar_t__ REDIS_OK ; 
 scalar_t__ __redisAppendCommand (int /*<<< orphan*/ *,char const*,size_t) ; 

int redisAppendFormattedCommand(redisContext *c, const char *cmd, size_t len) {

    if (__redisAppendCommand(c, cmd, len) != REDIS_OK) {
        return REDIS_ERR;
    }

    return REDIS_OK;
}
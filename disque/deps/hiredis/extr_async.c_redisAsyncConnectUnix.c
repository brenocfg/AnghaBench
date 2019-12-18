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
typedef  int /*<<< orphan*/  redisAsyncContext ;

/* Variables and functions */
 int /*<<< orphan*/  __redisAsyncCopyError (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * redisAsyncInitialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * redisConnectUnixNonBlock (char const*) ; 
 int /*<<< orphan*/  redisFree (int /*<<< orphan*/ *) ; 

redisAsyncContext *redisAsyncConnectUnix(const char *path) {
    redisContext *c;
    redisAsyncContext *ac;

    c = redisConnectUnixNonBlock(path);
    if (c == NULL)
        return NULL;

    ac = redisAsyncInitialize(c);
    if (ac == NULL) {
        redisFree(c);
        return NULL;
    }

    __redisAsyncCopyError(ac);
    return ac;
}
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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  __redisSetError (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  errno ; 
 size_t snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  strerror_r (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void __redisSetErrorFromErrno(redisContext *c, int type, const char *prefix) {
    char buf[128] = { 0 };
    size_t len = 0;

    if (prefix != NULL)
        len = snprintf(buf,sizeof(buf),"%s: ",prefix);
    strerror_r(errno,buf+len,sizeof(buf)-len);
    __redisSetError(c,type,buf);
}
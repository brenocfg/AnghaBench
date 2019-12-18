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

/* Variables and functions */
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 char* getenv (char*) ; 
 scalar_t__ read (int,char*,int) ; 
 int rjobfd ; 
 char* strstr (char*,char*) ; 
 scalar_t__ strtol (char*,char**,int) ; 
 int wjobfd ; 

__attribute__((used)) static int
readtokens()
{
    int n = 1;
    char c, *s;
    char *v = getenv("MAKEFLAGS");
    if (v == NULL)
        return n;
    if ((s = strstr(v, " --jobserver-fds="))) {
        rjobfd = (int)strtol(s+17, &s, 10);  /* skip " --jobserver-fds=" */
        wjobfd = (int)strtol(s+1, NULL, 10); /* skip comma */
    }
    if (rjobfd >= 0) {
        fcntl(rjobfd, F_SETFL, fcntl(rjobfd, F_GETFL)|O_NONBLOCK);
        while (read(rjobfd, &c, 1) > 0) {
            n++;
        }
    }
    return n;
}
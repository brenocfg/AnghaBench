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
 int /*<<< orphan*/  execlp (char*,char*,char*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fork () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int srvpid ; 
 int /*<<< orphan*/  twarn (char*) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static void
muststart(char *a0, char *a1, char *a2, char *a3, char *a4)
{
    srvpid = fork();
    if (srvpid < 0) {
        twarn("fork");
        exit(1);
    }

    if (srvpid > 0) {
        printf("%s %s %s %s %s\n", a0, a1, a2, a3, a4);
        printf("start server pid=%d\n", srvpid);
        usleep(100000); // .1s; time for the child to bind to its port
        return;
    }

    /* now in child */

    execlp(a0, a0, a1, a2, a3, a4, NULL);
}
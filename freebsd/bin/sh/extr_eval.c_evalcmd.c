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
 int /*<<< orphan*/  STARTSTACKSTR (char*) ; 
 int /*<<< orphan*/  STPUTC (char,char*) ; 
 int /*<<< orphan*/  STPUTS (char*,char*) ; 
 int /*<<< orphan*/  builtin_flags ; 
 int /*<<< orphan*/  evalstring (char*,int /*<<< orphan*/ ) ; 
 int exitstatus ; 
 char* grabstackstr (char*) ; 

int
evalcmd(int argc, char **argv)
{
        char *p;
        char *concat;
        char **ap;

        if (argc > 1) {
                p = argv[1];
                if (argc > 2) {
                        STARTSTACKSTR(concat);
                        ap = argv + 2;
                        for (;;) {
                                STPUTS(p, concat);
                                if ((p = *ap++) == NULL)
                                        break;
                                STPUTC(' ', concat);
                        }
                        STPUTC('\0', concat);
                        p = grabstackstr(concat);
                }
                evalstring(p, builtin_flags);
        } else
                exitstatus = 0;
        return exitstatus;
}
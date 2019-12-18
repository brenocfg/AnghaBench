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
 int /*<<< orphan*/  Usage (char*) ; 
 int dlg_count_argv (char**) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,char*) ; 
 scalar_t__ strtol (char*,char**,int) ; 

__attribute__((used)) static int
numeric_arg(char **av, int n)
{
    int result = 0;

    if (n < dlg_count_argv(av)) {
	char msg[80];
	char *last = 0;
	result = (int) strtol(av[n], &last, 10);

	if (last == 0 || *last != 0) {
	    sprintf(msg, "Expected a number for token %d of %.20s", n, av[0]);
	    Usage(msg);
	}
    }
    return result;
}
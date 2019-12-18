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
 int arg_rest (char**) ; 

__attribute__((used)) static char *
optional_str(char **av, int n, char *dft)
{
    char *ret = dft;
    if (arg_rest(av) > n)
	ret = av[n];
    return ret;
}
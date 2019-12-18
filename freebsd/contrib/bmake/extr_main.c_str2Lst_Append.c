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
typedef  int /*<<< orphan*/  Lst ;

/* Variables and functions */
 int /*<<< orphan*/  Lst_AtEnd (int /*<<< orphan*/ ,char*) ; 
 char* strtok (char*,char const*) ; 

int
str2Lst_Append(Lst lp, char *str, const char *sep)
{
    char *cp;
    int n;

    if (!sep)
	sep = " \t";

    for (n = 0, cp = strtok(str, sep); cp; cp = strtok(NULL, sep)) {
	(void)Lst_AtEnd(lp, cp);
	n++;
    }
    return (n);
}
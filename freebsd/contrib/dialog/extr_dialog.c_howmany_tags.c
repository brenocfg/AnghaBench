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
 char* _ (char*) ; 
 int arg_rest (char**) ; 
 scalar_t__ isOption (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char const*,int,int) ; 

__attribute__((used)) static int
howmany_tags(char *argv[], int group)
{
    int result = 0;
    int have;
    char temp[80];

    while (argv[0] != 0) {
	if (isOption(argv[0]))
	    break;
	if ((have = arg_rest(argv)) < group) {
	    const char *format = _("Expected %d arguments, found only %d");
	    sprintf(temp, format, group, have);
	    Usage(temp);
	} else if ((have % group) != 0) {
	    const char *format = _("Expected %d arguments, found extra %d");
	    sprintf(temp, format, group, (have % group));
	    Usage(temp);
	}

	argv += have;
	result += (have / group);
    }

    return result;
}
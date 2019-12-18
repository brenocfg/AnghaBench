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
 int MAX_INT_PARAM ; 
 int /*<<< orphan*/  internal_setup (char*,int*) ; 
 scalar_t__ isdigit (char) ; 
 int simple_strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int option_setup(char *str)
{
	int ints[MAX_INT_PARAM];
	char *cur = str;
	int i = 1;

	while (cur && isdigit(*cur) && i <= MAX_INT_PARAM) {
		ints[i++] = simple_strtoul(cur, NULL, 0);

		if ((cur = strchr(cur, ',')) != NULL)
			cur++;
	}

	ints[0] = i - 1;
	internal_setup(cur, ints);
	return 1;
}
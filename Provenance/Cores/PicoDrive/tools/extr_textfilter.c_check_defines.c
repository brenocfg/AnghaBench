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
 scalar_t__ isspace (char) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int check_defines(const char **defs, int defcount, char *tdef)
{
	int i, len;

	while (isspace(*tdef)) tdef++;
	len = strlen(tdef);
	for (i = 0; i < len; i++)
		if (tdef[i] == ' ' || tdef[i] == '\r' || tdef[i] == '\n') break;
	tdef[i] = 0;

	for (i = 0; i < defcount; i++)
	{
		if (strcmp(defs[i], tdef) == 0)
			return 1;
	}

	return 0;
}
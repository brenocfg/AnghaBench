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
 int MAXMEM ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

void trim_str(char *str)
{
	char tmp[MAXMEM];
	int start, end, j, i;

	start = 0;
	end = strlen(str) - 1;
	j = 0;
	while (start < strlen(str) && isspace(str[start])) start++;
	while (end >= 0 && isspace(str[end])) end--;

	for (i = start; i <= end; ++i)
		tmp[j++] = str[i];

	tmp[j] = '\0';
	strcpy(str, tmp);

	return;
}
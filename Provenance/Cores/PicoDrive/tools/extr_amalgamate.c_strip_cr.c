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
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 

__attribute__((used)) static void strip_cr(char *str)
{
	int len = strlen(str);
	char *p = str;

	while ((p = strchr(p, '\r')))
	{
		memmove(p, p + 1, len - (p - str) + 1);
	}
	if (strlen(str) > 0)
	{
		p = str + strlen(str) - 1;
		while (p >= str && isspace(*p)) { *p = 0; p--; } // strip spaces on line ends
	}
	strcat(str, "\n"); // re-add newline
}
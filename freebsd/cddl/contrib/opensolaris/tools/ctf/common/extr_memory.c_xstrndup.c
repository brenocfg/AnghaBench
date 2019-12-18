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
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memory_bailout () ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 

char *
xstrndup(char *str, size_t len)
{
	char *newstr;

	if ((newstr = malloc(len + 1)) == NULL)
		memory_bailout();

	(void) strncpy(newstr, str, len);
	newstr[len] = '\0';

	return (newstr);
}
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
 int /*<<< orphan*/  nomem () ; 
 char* strdup (char*) ; 

__attribute__((used)) static char *
safe_strdup(char *str)
{
	char *dupstr = strdup(str);

	if (dupstr == NULL)
		nomem();

	return (dupstr);
}
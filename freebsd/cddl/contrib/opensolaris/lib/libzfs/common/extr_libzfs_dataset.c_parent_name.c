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
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static int
parent_name(const char *path, char *buf, size_t buflen)
{
	char *slashp;

	(void) strlcpy(buf, path, buflen);

	if ((slashp = strrchr(buf, '/')) == NULL)
		return (-1);
	*slashp = '\0';

	return (0);
}
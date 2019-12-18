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
 char* strcpy (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  xalloc (scalar_t__) ; 

__attribute__((used)) static char *
savestr(const char *s)
{

	if (s == NULL)
		return (NULL);
	return (strcpy(xalloc(strlen(s) + 1), s));
}
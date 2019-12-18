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
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int strlen (char const*) ; 
 char* xmalloc (size_t) ; 

__attribute__((used)) static char *
xstrdup(const char *name)
{
	size_t n;
	char *s;

	if (name == NULL) {
		return NULL;
	}
	n = strlen(name) + 1;
	s = xmalloc(n);
	memcpy(s, name, n);
	return s;
}
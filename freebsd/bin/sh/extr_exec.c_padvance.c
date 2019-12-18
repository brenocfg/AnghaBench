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
 int /*<<< orphan*/  CHECKSTRSPACE (size_t,char*) ; 
 int /*<<< orphan*/  STARTSTACKSTR (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char* stalloc (size_t) ; 
 size_t strlen (char const*) ; 

char *
padvance(const char **path, const char **popt, const char *name)
{
	const char *p, *start;
	char *q;
	size_t len, namelen;

	if (*path == NULL)
		return NULL;
	start = *path;
	if (popt != NULL)
		for (p = start; *p && *p != ':' && *p != '%'; p++)
			; /* nothing */
	else
		for (p = start; *p && *p != ':'; p++)
			; /* nothing */
	namelen = strlen(name);
	len = p - start + namelen + 2;	/* "2" is for '/' and '\0' */
	STARTSTACKSTR(q);
	CHECKSTRSPACE(len, q);
	if (p != start) {
		memcpy(q, start, p - start);
		q += p - start;
		*q++ = '/';
	}
	memcpy(q, name, namelen + 1);
	if (popt != NULL) {
		if (*p == '%') {
			*popt = ++p;
			while (*p && *p != ':')  p++;
		} else
			*popt = NULL;
	}
	if (*p == ':')
		*path = p + 1;
	else
		*path = NULL;
	return stalloc(len);
}
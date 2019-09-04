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
 int /*<<< orphan*/  EINVAL ; 
 size_t NAME_MAX ; 
 char* __gettextdomain () ; 
 char* current_domain ; 
 int /*<<< orphan*/  errno ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

char *textdomain(const char *domainname)
{
	if (!domainname) return __gettextdomain();

	size_t domlen = strlen(domainname);
	if (domlen > NAME_MAX) {
		errno = EINVAL;
		return 0;
	}

	if (!current_domain) {
		current_domain = malloc(NAME_MAX+1);
		if (!current_domain) return 0;
	}

	memcpy(current_domain, domainname, domlen+1);

	return current_domain;
}
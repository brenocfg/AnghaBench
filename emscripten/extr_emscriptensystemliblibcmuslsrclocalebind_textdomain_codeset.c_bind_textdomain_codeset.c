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
 int /*<<< orphan*/  errno ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

char *bind_textdomain_codeset(const char *domainname, const char *codeset)
{
	if (codeset && strcasecmp(codeset, "UTF-8"))
		errno = EINVAL;
	return NULL;
}
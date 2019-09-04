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
 scalar_t__ EEXIST ; 
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  __randname (char*) ; 
 scalar_t__ errno ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  mkdir (char*,int) ; 
 size_t strlen (char*) ; 

char *mkdtemp(char *template)
{
	size_t l = strlen(template);
	int retries = 100;

	if (l<6 || memcmp(template+l-6, "XXXXXX", 6)) {
		errno = EINVAL;
		return 0;
	}

	do {
		__randname(template+l-6);
		if (!mkdir(template, 0700)) return template;
	} while (--retries && errno == EEXIST);

	memcpy(template+l-6, "XXXXXX", 6);
	return 0;
}
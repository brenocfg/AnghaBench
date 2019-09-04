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
struct stat {int dummy; } ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 scalar_t__ EINVAL ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  __randname (char*) ; 
 scalar_t__ errno ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 size_t strlen (char*) ; 

char *mktemp(char *template)
{
	size_t l = strlen(template);
	int retries = 100;
	struct stat st;

	if (l < 6 || memcmp(template+l-6, "XXXXXX", 6)) {
		errno = EINVAL;
		*template = 0;
		return template;
	}

	do {
		__randname(template+l-6);
		if (stat(template, &st)) {
			if (errno != ENOENT) *template = 0;
			return template;
		}
	} while (--retries);

	*template = 0;
	errno = EEXIST;
	return template;
}
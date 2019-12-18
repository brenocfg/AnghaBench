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
 int /*<<< orphan*/  ENAMETOOLONG ; 
 char* demangle (char const*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 unsigned int is_mangled (char const*,unsigned int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 

int
elftc_demangle(const char *mangledname, char *buffer, size_t bufsize,
    unsigned int flags)
{
	unsigned int style, rc;
	char *rlt;

	style = flags & 0xFFFF;
	rc = flags >> 16;

	if (mangledname == NULL ||
	    ((style = is_mangled(mangledname, style)) == 0)) {
		errno = EINVAL;
		return (-1);
	}

	if ((rlt = demangle(mangledname, style, rc)) == NULL) {
		errno = EINVAL;
		return (-1);
	}

	if (buffer == NULL || bufsize < strlen(rlt) + 1) {
		free(rlt);
		errno = ENAMETOOLONG;
		return (-1);
	}

	strncpy(buffer, rlt, bufsize);
	buffer[bufsize - 1] = '\0';
	free(rlt);

	return (0);
}
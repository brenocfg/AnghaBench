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
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  memmove (char*,char*,unsigned int) ; 
 unsigned int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,unsigned int) ; 

__attribute__((used)) static int strip_rcs_crap(char *version)
{
	unsigned int len, full_len;

	if (strncmp(version, "$Revision", strlen("$Revision")) != 0)
		return 0;

	/* Space for version string follows. */
	full_len = strlen(version) + strlen(version + strlen(version) + 1) + 2;

	/* Move string to start with version number: prefix will be
	 * $Revision$ or $Revision: */
	len = strlen("$Revision");
	if (version[len] == ':' || version[len] == '$')
		len++;
	while (isspace(version[len]))
		len++;
	memmove(version, version+len, full_len-len);
	full_len -= len;

	/* Preserve up to next whitespace. */
	len = 0;
	while (version[len] && !isspace(version[len]))
		len++;
	memmove(version + len, version + strlen(version),
		full_len - strlen(version));
	return 1;
}
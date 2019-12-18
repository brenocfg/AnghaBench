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
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IsInclude (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ isspace (unsigned char) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static Boolean
IsSysVInclude(const char *line)
{
	const char *p;

	if (!IsInclude(line, TRUE))
		return FALSE;

	/* Avoid interpeting a dependency line as an include */
	for (p = line; (p = strchr(p, ':')) != NULL;) {
		if (*++p == '\0') {
			/* end of line -> dependency */
			return FALSE;
		}
		if (*p == ':' || isspace((unsigned char)*p)) {
			/* :: operator or ': ' -> dependency */
			return FALSE;
		}
	}
	return TRUE;
}
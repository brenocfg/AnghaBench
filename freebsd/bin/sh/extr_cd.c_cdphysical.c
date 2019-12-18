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
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 scalar_t__ chdir (char*) ; 
 char* findcwd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  updatepwd (char*) ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static int
cdphysical(char *dest)
{
	char *p;
	int rc = 0;

	INTOFF;
	if (chdir(dest) < 0) {
		INTON;
		return (-1);
	}
	p = findcwd(NULL);
	if (p == NULL) {
		warning("warning: failed to get name of current directory");
		rc = 1;
	}
	updatepwd(p);
	INTON;
	return (rc);
}
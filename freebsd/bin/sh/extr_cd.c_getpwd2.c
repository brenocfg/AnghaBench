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
 scalar_t__ ERANGE ; 
 int MAXPWD ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/ * getcwd (char*,int) ; 
 char* stalloc (int) ; 
 int /*<<< orphan*/  stunalloc (char*) ; 

__attribute__((used)) static char *
getpwd2(void)
{
	char *pwd;
	int i;

	for (i = MAXPWD;; i *= 2) {
		pwd = stalloc(i);
		if (getcwd(pwd, i) != NULL)
			return pwd;
		stunalloc(pwd);
		if (errno != ERANGE)
			break;
	}

	return NULL;
}
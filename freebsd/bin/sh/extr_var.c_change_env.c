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
 int /*<<< orphan*/  ckfree (char*) ; 
 char* savestr (char const*) ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  unsetenv (char*) ; 

__attribute__((used)) static void
change_env(const char *s, int set)
{
	char *eqp;
	char *ss;

	INTOFF;
	ss = savestr(s);
	if ((eqp = strchr(ss, '=')) != NULL)
		*eqp = '\0';
	if (set && eqp != NULL)
		(void) setenv(ss, eqp + 1, 1);
	else
		(void) unsetenv(ss);
	ckfree(ss);
	INTON;

	return;
}
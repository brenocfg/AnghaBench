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
 int /*<<< orphan*/  LOG_ERR ; 
 int define_macro (char*,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
do_macro(char *arg)
{
	char *eq;
	int err;

	if ((eq = strchr(arg, '=')) == NULL)
		err = define_macro(arg, "");
	else {
		*eq++ = '\0';
		err = define_macro(arg, eq);
	}
	if (err == -1) {
		syslog(LOG_ERR, "cannot save macro: %m");
		exit(1);
	}
}
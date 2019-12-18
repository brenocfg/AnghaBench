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
 int /*<<< orphan*/  STATUS_BADUSAGE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 char* getprogname () ; 
 scalar_t__ pgrep ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
	const char *ustr;

	if (pgrep)
		ustr = "[-LSfilnoqvx] [-d delim]";
	else
		ustr = "[-signal] [-ILfilnovx]";

	fprintf(stderr,
		"usage: %s %s [-F pidfile] [-G gid] [-M core] [-N system]\n"
		"             [-P ppid] [-U uid] [-c class] [-g pgrp] [-j jail]\n"
		"             [-s sid] [-t tty] [-u euid] pattern ...\n",
		getprogname(), ustr);

	exit(STATUS_BADUSAGE);
}
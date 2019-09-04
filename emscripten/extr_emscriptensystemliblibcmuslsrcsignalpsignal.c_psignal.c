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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  stderr ; 
 char* strsignal (int) ; 

void psignal(int sig, const char *msg)
{
	char *s = strsignal(sig);
	if (msg) fprintf(stderr, "%s: %s\n", msg, s);
	else fprintf(stderr, "%s\n", s);
}
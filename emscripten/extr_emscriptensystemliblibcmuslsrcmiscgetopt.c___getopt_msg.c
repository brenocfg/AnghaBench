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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* __lctrans_cur (char const*) ; 
 int /*<<< orphan*/  flockfile (int /*<<< orphan*/ *) ; 
 scalar_t__ fputs (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  funlockfile (int /*<<< orphan*/ *) ; 
 size_t fwrite (char const*,int,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ putc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stderr ; 
 int strlen (char const*) ; 

void __getopt_msg(const char *a, const char *b, const char *c, size_t l)
{
	FILE *f = stderr;
	b = __lctrans_cur(b);
	flockfile(f);
	fputs(a, f)>=0
	&& fwrite(b, strlen(b), 1, f)
	&& fwrite(c, 1, l, f)==l
	&& putc('\n', f);
	funlockfile(f);
}
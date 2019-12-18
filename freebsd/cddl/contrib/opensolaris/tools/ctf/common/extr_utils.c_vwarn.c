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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* pname ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  vfprintf (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

void
vwarn(const char *format, va_list alist)
{
	int err = errno;

	if (pname != NULL)
		(void) fprintf(stderr, "%s: ", pname);

	(void) vfprintf(stderr, format, alist);

	if (strchr(format, '\n') == NULL)
		(void) fprintf(stderr, ": %s\n", strerror(err));
}
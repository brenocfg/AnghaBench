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
 char* ERRNO_FMT ; 
 char* PNAME_FMT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pname ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * strerror (int) ; 
 int /*<<< orphan*/ * strrchr (char const*,char) ; 
 int /*<<< orphan*/  vfprintf (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uu_warn_internal(int err, const char *format, va_list alist)
{
	if (pname != NULL)
		(void) fprintf(stderr, PNAME_FMT, pname);

	(void) vfprintf(stderr, format, alist);

	if (strrchr(format, '\n') == NULL)
		(void) fprintf(stderr, ERRNO_FMT, strerror(err));
}
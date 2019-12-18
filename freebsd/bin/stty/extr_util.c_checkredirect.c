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
struct stat {scalar_t__ st_rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  fstat (int /*<<< orphan*/ ,struct stat*) ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*) ; 

void
checkredirect(void)
{
	struct stat sb1, sb2;

	if (isatty(STDOUT_FILENO) && isatty(STDERR_FILENO) &&
	    !fstat(STDOUT_FILENO, &sb1) && !fstat(STDERR_FILENO, &sb2) &&
	    (sb1.st_rdev != sb2.st_rdev))
warnx("stdout appears redirected, but stdin is the control descriptor");
}
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
 char* ELFTC_GETPROGNAME () ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 char* archive_version_string () ; 
 char* elftc_version () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*) ; 

__attribute__((used)) static void
bsdar_version(void)
{
	(void)printf("%s (%s, %s)\n", ELFTC_GETPROGNAME(), archive_version_string(),
	    elftc_version());
	exit(EXIT_SUCCESS);
}
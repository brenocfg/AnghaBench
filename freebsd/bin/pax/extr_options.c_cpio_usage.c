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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

void
cpio_usage(void)
{
	(void)fputs("usage: cpio -o [-aABcLvVzZ] [-C bytes] [-H format] [-O archive]\n", stderr);
	(void)fputs("               [-F archive] < name-list [> archive]\n", stderr);
	(void)fputs("       cpio -i [-bBcdfmnrsStuvVzZ6] [-C bytes] [-E file] [-H format]\n", stderr);
	(void)fputs("               [-I archive] [-F archive] [pattern...] [< archive]\n", stderr);
	(void)fputs("       cpio -p [-adlLmuvV] destination-directory < name-list\n", stderr);
	exit(1);
}
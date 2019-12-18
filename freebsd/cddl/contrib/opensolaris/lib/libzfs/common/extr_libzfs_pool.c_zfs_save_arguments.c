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
 int /*<<< orphan*/  basename (char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 

void
zfs_save_arguments(int argc, char **argv, char *string, int len)
{
	(void) strlcpy(string, basename(argv[0]), len);
	for (int i = 1; i < argc; i++) {
		(void) strlcat(string, " ", len);
		(void) strlcat(string, argv[i], len);
	}
}
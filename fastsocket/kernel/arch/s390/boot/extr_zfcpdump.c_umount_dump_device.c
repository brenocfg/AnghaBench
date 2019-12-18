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
 int /*<<< orphan*/  DUMP_DIR ; 
 int /*<<< orphan*/  PRINT_PERR (char*) ; 
 scalar_t__ umount (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int umount_dump_device(void)
{
	if (umount(DUMP_DIR) != 0) {
		PRINT_PERR("umount failed\n");
		return -1;
	}
	return 0;
}
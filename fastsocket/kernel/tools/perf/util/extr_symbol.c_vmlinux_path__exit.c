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
 int /*<<< orphan*/  free (int /*<<< orphan*/ ******) ; 
 int /*<<< orphan*/ ****** vmlinux_path ; 
 scalar_t__ vmlinux_path__nr_entries ; 

__attribute__((used)) static void vmlinux_path__exit(void)
{
	while (--vmlinux_path__nr_entries >= 0) {
		free(vmlinux_path[vmlinux_path__nr_entries]);
		vmlinux_path[vmlinux_path__nr_entries] = NULL;
	}

	free(vmlinux_path);
	vmlinux_path = NULL;
}
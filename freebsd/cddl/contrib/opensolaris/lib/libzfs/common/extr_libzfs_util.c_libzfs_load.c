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
 scalar_t__ EEXIST ; 
 scalar_t__ errno ; 
 scalar_t__ kldload (char*) ; 
 scalar_t__ modfind (char*) ; 

__attribute__((used)) static int
libzfs_load(void)
{
	int error;

	if (modfind("zfs") < 0) {
		/* Not present in kernel, try loading it. */
		if (kldload("zfs") < 0 || modfind("zfs") < 0) {
			if (errno != EEXIST)
				return (-1);
		}
	}
	return (0);
}
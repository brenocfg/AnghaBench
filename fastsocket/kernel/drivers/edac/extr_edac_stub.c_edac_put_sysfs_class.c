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
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edac_class ; 
 int /*<<< orphan*/  edac_class_valid ; 
 int /*<<< orphan*/  sysdev_class_unregister (int /*<<< orphan*/ *) ; 

void edac_put_sysfs_class(void)
{
	/* last user unregisters it */
	if (atomic_dec_and_test(&edac_class_valid))
		sysdev_class_unregister(&edac_class);
}
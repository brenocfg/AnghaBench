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
 int /*<<< orphan*/  IPATH_NMINORS ; 
 int /*<<< orphan*/  class_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev ; 
 int /*<<< orphan*/ * ipath_class ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void user_cleanup(void)
{
	if (ipath_class) {
		class_destroy(ipath_class);
		ipath_class = NULL;
	}

	unregister_chrdev_region(dev, IPATH_NMINORS);
}
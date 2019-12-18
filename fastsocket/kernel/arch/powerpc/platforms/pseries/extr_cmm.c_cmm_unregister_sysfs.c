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
struct sys_device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmm_attrs ; 
 int /*<<< orphan*/  cmm_sysdev_class ; 
 int /*<<< orphan*/  sysdev_class_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysdev_remove_file (struct sys_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysdev_unregister (struct sys_device*) ; 

__attribute__((used)) static void cmm_unregister_sysfs(struct sys_device *sysdev)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(cmm_attrs); i++)
		sysdev_remove_file(sysdev, cmm_attrs[i]);
	sysdev_unregister(sysdev);
	sysdev_class_unregister(&cmm_sysdev_class);
}
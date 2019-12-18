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
struct se_subsystem_api {int /*<<< orphan*/  (* set_configfs_dev_params ) (struct se_device*,char const*,size_t) ;} ;
struct se_device {struct se_subsystem_api* transport; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct se_device*,char const*,size_t) ; 

__attribute__((used)) static ssize_t target_core_store_dev_control(
	void *p,
	const char *page,
	size_t count)
{
	struct se_device *dev = p;
	struct se_subsystem_api *t = dev->transport;

	return t->set_configfs_dev_params(dev, page, count);
}
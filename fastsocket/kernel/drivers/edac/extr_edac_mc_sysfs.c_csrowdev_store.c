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
struct kobject {int dummy; } ;
struct csrowdev_attribute {int /*<<< orphan*/  private; int /*<<< orphan*/  (* store ) (struct csrow_info*,char const*,size_t,int /*<<< orphan*/ ) ;} ;
struct csrow_info {int dummy; } ;
struct attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  stub1 (struct csrow_info*,char const*,size_t,int /*<<< orphan*/ ) ; 
 struct csrow_info* to_csrow (struct kobject*) ; 
 struct csrowdev_attribute* to_csrowdev_attr (struct attribute*) ; 

__attribute__((used)) static ssize_t csrowdev_store(struct kobject *kobj, struct attribute *attr,
			const char *buffer, size_t count)
{
	struct csrow_info *csrow = to_csrow(kobj);
	struct csrowdev_attribute *csrowdev_attr = to_csrowdev_attr(attr);

	if (csrowdev_attr->store)
		return csrowdev_attr->store(csrow,
					buffer,
					count, csrowdev_attr->private);
	return -EIO;
}
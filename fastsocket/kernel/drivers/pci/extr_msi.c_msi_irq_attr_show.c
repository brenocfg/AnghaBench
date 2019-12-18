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
struct msi_desc {int dummy; } ;
struct msi_attribute {int /*<<< orphan*/  (* show ) (struct msi_desc*,struct msi_attribute*,char*) ;} ;
struct kobject {int dummy; } ;
struct attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  stub1 (struct msi_desc*,struct msi_attribute*,char*) ; 
 struct msi_attribute* to_msi_attr (struct attribute*) ; 
 struct msi_desc* to_msi_desc (struct kobject*) ; 

__attribute__((used)) static ssize_t msi_irq_attr_show(struct kobject *kobj,
				 struct attribute *attr, char *buf)
{
	struct msi_attribute *attribute = to_msi_attr(attr);
	struct msi_desc *entry = to_msi_desc(kobj);

	if (!attribute->show)
		return -EIO;

	return attribute->show(entry, attribute, buf);
}
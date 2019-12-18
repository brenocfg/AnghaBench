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
struct efivar_entry {int dummy; } ;
struct efivar_attribute {int /*<<< orphan*/  (* show ) (struct efivar_entry*,char*) ;} ;
struct attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct efivar_entry*,char*) ; 
 struct efivar_attribute* to_efivar_attr (struct attribute*) ; 
 struct efivar_entry* to_efivar_entry (struct kobject*) ; 

__attribute__((used)) static ssize_t efivar_attr_show(struct kobject *kobj, struct attribute *attr,
				char *buf)
{
	struct efivar_entry *var = to_efivar_entry(kobj);
	struct efivar_attribute *efivar_attr = to_efivar_attr(attr);
	ssize_t ret = -EIO;

	if (!capable(CAP_SYS_ADMIN))
		return -EACCES;

	if (efivar_attr->show) {
		ret = efivar_attr->show(var, buf);
	}
	return ret;
}
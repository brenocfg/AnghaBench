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
struct kobj_attribute {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int MAX_DRC_NAME_LEN ; 
 int dlpar_remove_slot (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static ssize_t remove_slot_store(struct kobject *kobj,
				 struct kobj_attribute *attr,
				 const char *buf, size_t nbytes)
{
	char drc_name[MAX_DRC_NAME_LEN];
	int rc;
	char *end;

	if (nbytes >= MAX_DRC_NAME_LEN)
		return 0;

	memcpy(drc_name, buf, nbytes);

	end = strchr(drc_name, '\n');
	if (!end)
		end = &drc_name[nbytes];
	*end = '\0';

	rc = dlpar_remove_slot(drc_name);
	if (rc)
		return rc;

	return nbytes;
}
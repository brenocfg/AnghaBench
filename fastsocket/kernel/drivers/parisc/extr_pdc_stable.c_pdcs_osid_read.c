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
 int EINVAL ; 
 char* os_id_to_string (int) ; 
 int pdcs_osid ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 

__attribute__((used)) static ssize_t pdcs_osid_read(struct kobject *kobj,
			      struct kobj_attribute *attr, char *buf)
{
	char *out = buf;

	if (!buf)
		return -EINVAL;

	out += sprintf(out, "%s dependent data (0x%.4x)\n",
		os_id_to_string(pdcs_osid), pdcs_osid);

	return out - buf;
}
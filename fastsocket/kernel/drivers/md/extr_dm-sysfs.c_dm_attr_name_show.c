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
struct mapped_device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 scalar_t__ dm_copy_name_and_uuid (struct mapped_device*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static ssize_t dm_attr_name_show(struct mapped_device *md, char *buf)
{
	if (dm_copy_name_and_uuid(md, buf, NULL))
		return -EIO;

	strcat(buf, "\n");
	return strlen(buf);
}
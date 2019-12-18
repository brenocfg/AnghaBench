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
typedef  int u32 ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int ARRAY_SIZE (char**) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static ssize_t cxacru_sysfs_showattr_bool(u32 value, char *buf)
{
	static char *str[] = { "no", "yes" };
	if (unlikely(value >= ARRAY_SIZE(str)))
		return snprintf(buf, PAGE_SIZE, "%u\n", value);
	return snprintf(buf, PAGE_SIZE, "%s\n", str[value]);
}
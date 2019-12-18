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
typedef  int /*<<< orphan*/  u32 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  HPWMI_ALS_QUERY ; 
 int /*<<< orphan*/  hp_wmi_perform_query (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ssize_t set_als(struct device *dev, struct device_attribute *attr,
		       const char *buf, size_t count)
{
	u32 tmp = simple_strtoul(buf, NULL, 10);
	hp_wmi_perform_query(HPWMI_ALS_QUERY, 1, tmp);
	return count;
}
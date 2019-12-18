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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  pod_send_store_command (struct device*,char const*,size_t,int,int) ; 

__attribute__((used)) static ssize_t pod_set_store_amp_setup(struct device *dev,
				       struct device_attribute *attr,
				       const char *buf, size_t count)
{
	return pod_send_store_command(dev, buf, count, 0x0040, 0x0100);
}
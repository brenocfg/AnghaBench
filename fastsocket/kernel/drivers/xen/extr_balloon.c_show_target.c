#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sysdev_attribute {int dummy; } ;
struct sys_device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {scalar_t__ target_pages; } ;

/* Variables and functions */
 unsigned long long PAGE_SHIFT ; 
 TYPE_1__ balloon_stats ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long long) ; 

__attribute__((used)) static ssize_t show_target(struct sys_device *dev, struct sysdev_attribute *attr,
			      char *buf)
{
	return sprintf(buf, "%llu\n",
		       (unsigned long long)balloon_stats.target_pages
		       << PAGE_SHIFT);
}
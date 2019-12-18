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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cpumask {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 struct cpumask* cpumask_of_pcibus (int /*<<< orphan*/ ) ; 
 int cpumask_scnprintf (char*,scalar_t__,struct cpumask const*) ; 
 TYPE_1__* to_pci_dev (struct device*) ; 

__attribute__((used)) static ssize_t local_cpus_show(struct device *dev,
			struct device_attribute *attr, char *buf)
{		
	const struct cpumask *mask;
	int len;

	mask = cpumask_of_pcibus(to_pci_dev(dev)->bus);
	len = cpumask_scnprintf(buf, PAGE_SIZE-2, mask);
	buf[len++] = '\n';
	buf[len] = '\0';
	return len;
}
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
struct device {int dummy; } ;
struct attribute_group {struct attribute** attrs; } ;
struct attribute {int dummy; } ;
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  dme1737_chmod_file (struct device*,struct attribute*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dme1737_chmod_group(struct device *dev,
				const struct attribute_group *group,
				mode_t mode)
{
	struct attribute **attr;

	for (attr = group->attrs; *attr; attr++) {
		dme1737_chmod_file(dev, *attr, mode);
	}
}
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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct device {TYPE_1__ kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_glue_dir (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cleanup_device_parent(struct device *dev)
{
	cleanup_glue_dir(dev, dev->kobj.parent);
}
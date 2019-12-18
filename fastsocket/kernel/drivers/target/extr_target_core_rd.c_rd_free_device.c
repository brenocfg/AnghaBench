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
struct se_device {int dummy; } ;
struct rd_dev {int dummy; } ;

/* Variables and functions */
 struct rd_dev* RD_DEV (struct se_device*) ; 
 int /*<<< orphan*/  kfree (struct rd_dev*) ; 
 int /*<<< orphan*/  rd_release_device_space (struct rd_dev*) ; 

__attribute__((used)) static void rd_free_device(struct se_device *dev)
{
	struct rd_dev *rd_dev = RD_DEV(dev);

	rd_release_device_space(rd_dev);
	kfree(rd_dev);
}
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
struct sbp2_target {int dummy; } ;
struct fw_unit {int /*<<< orphan*/  device; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct sbp2_target* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 struct fw_unit* fw_unit (struct device*) ; 
 int /*<<< orphan*/  sbp2_target_put (struct sbp2_target*) ; 

__attribute__((used)) static int sbp2_remove(struct device *dev)
{
	struct fw_unit *unit = fw_unit(dev);
	struct sbp2_target *tgt = dev_get_drvdata(&unit->device);

	sbp2_target_put(tgt);
	return 0;
}
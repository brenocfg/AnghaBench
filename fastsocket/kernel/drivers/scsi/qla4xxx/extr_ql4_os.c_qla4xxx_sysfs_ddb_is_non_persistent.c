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
struct iscsi_bus_flash_session {scalar_t__ flash_state; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ DEV_DB_NON_PERSISTENT ; 
 struct iscsi_bus_flash_session* iscsi_dev_to_flash_session (struct device*) ; 
 int /*<<< orphan*/  iscsi_flashnode_bus_match (struct device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qla4xxx_sysfs_ddb_is_non_persistent(struct device *dev, void *data)
{
	struct iscsi_bus_flash_session *fnode_sess;

	if (!iscsi_flashnode_bus_match(dev, NULL))
		return 0;

	fnode_sess = iscsi_dev_to_flash_session(dev);

	return (fnode_sess->flash_state == DEV_DB_NON_PERSISTENT);
}
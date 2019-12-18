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
struct genl_ops {int /*<<< orphan*/  ops_list; int /*<<< orphan*/  flags; scalar_t__ policy; int /*<<< orphan*/ * doit; int /*<<< orphan*/ * dumpit; int /*<<< orphan*/  cmd; } ;
struct genl_family {int /*<<< orphan*/  ops_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_CMD_NEWOPS ; 
 int EEXIST ; 
 int EINVAL ; 
 int /*<<< orphan*/  GENL_CMD_CAP_DO ; 
 int /*<<< orphan*/  GENL_CMD_CAP_DUMP ; 
 int /*<<< orphan*/  GENL_CMD_CAP_HASPOL ; 
 int /*<<< orphan*/  genl_ctrl_event (int /*<<< orphan*/ ,struct genl_ops*) ; 
 scalar_t__ genl_get_cmd (int /*<<< orphan*/ ,struct genl_family*) ; 
 int /*<<< orphan*/  genl_lock () ; 
 int /*<<< orphan*/  genl_unlock () ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int genl_register_ops(struct genl_family *family, struct genl_ops *ops)
{
	int err = -EINVAL;

	if (ops->dumpit == NULL && ops->doit == NULL)
		goto errout;

	if (genl_get_cmd(ops->cmd, family)) {
		err = -EEXIST;
		goto errout;
	}

	if (ops->dumpit)
		ops->flags |= GENL_CMD_CAP_DUMP;
	if (ops->doit)
		ops->flags |= GENL_CMD_CAP_DO;
	if (ops->policy)
		ops->flags |= GENL_CMD_CAP_HASPOL;

	genl_lock();
	list_add_tail(&ops->ops_list, &family->ops_list);
	genl_unlock();

	genl_ctrl_event(CTRL_CMD_NEWOPS, ops);
	err = 0;
errout:
	return err;
}
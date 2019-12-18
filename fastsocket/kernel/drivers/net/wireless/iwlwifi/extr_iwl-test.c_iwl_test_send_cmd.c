#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iwl_test {TYPE_2__* trans; TYPE_1__* ops; } ;
struct iwl_host_cmd {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  op_mode; } ;
struct TYPE_3__ {int (* send_cmd ) (int /*<<< orphan*/ ,struct iwl_host_cmd*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,struct iwl_host_cmd*) ; 

__attribute__((used)) static inline int iwl_test_send_cmd(struct iwl_test *tst,
				    struct iwl_host_cmd *cmd)
{
	return tst->ops->send_cmd(tst->trans->op_mode, cmd);
}
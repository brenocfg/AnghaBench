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
struct iwl_trans {int /*<<< orphan*/  state; int /*<<< orphan*/ * op_mode; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* stop_hw ) (struct iwl_trans*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_TRANS_NO_FW ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  stub1 (struct iwl_trans*,int) ; 

__attribute__((used)) static inline void iwl_trans_stop_hw(struct iwl_trans *trans,
				     bool op_mode_leaving)
{
	might_sleep();

	trans->ops->stop_hw(trans, op_mode_leaving);

	if (op_mode_leaving)
		trans->op_mode = NULL;

	trans->state = IWL_TRANS_NO_FW;
}
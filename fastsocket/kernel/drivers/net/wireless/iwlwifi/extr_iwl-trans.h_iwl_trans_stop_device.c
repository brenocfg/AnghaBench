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
struct iwl_trans {int /*<<< orphan*/  state; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* stop_device ) (struct iwl_trans*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_TRANS_NO_FW ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  stub1 (struct iwl_trans*) ; 

__attribute__((used)) static inline void iwl_trans_stop_device(struct iwl_trans *trans)
{
	might_sleep();

	trans->ops->stop_device(trans);

	trans->state = IWL_TRANS_NO_FW;
}
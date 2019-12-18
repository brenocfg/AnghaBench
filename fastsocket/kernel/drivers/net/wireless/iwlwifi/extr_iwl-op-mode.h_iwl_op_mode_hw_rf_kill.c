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
struct iwl_op_mode {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* hw_rf_kill ) (struct iwl_op_mode*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  stub1 (struct iwl_op_mode*,int) ; 

__attribute__((used)) static inline void iwl_op_mode_hw_rf_kill(struct iwl_op_mode *op_mode,
					  bool state)
{
	might_sleep();
	op_mode->ops->hw_rf_kill(op_mode, state);
}
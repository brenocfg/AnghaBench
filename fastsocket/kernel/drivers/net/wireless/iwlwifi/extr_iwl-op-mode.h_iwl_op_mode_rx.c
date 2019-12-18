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
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_op_mode {TYPE_1__* ops; } ;
struct iwl_device_cmd {int dummy; } ;
struct TYPE_2__ {int (* rx ) (struct iwl_op_mode*,struct iwl_rx_cmd_buffer*,struct iwl_device_cmd*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  might_sleep () ; 
 int stub1 (struct iwl_op_mode*,struct iwl_rx_cmd_buffer*,struct iwl_device_cmd*) ; 

__attribute__((used)) static inline int iwl_op_mode_rx(struct iwl_op_mode *op_mode,
				  struct iwl_rx_cmd_buffer *rxb,
				  struct iwl_device_cmd *cmd)
{
	might_sleep();
	return op_mode->ops->rx(op_mode, rxb, cmd);
}
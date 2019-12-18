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
typedef  int /*<<< orphan*/  ccv_nnc_tensor_symbol_t ;
typedef  int /*<<< orphan*/  (* ccv_cnnp_state_initializer_f ) (void* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ;
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  hint; int /*<<< orphan*/  cmd; } ;
typedef  TYPE_1__ ccv_cnnp_cmd_exec_io_set_by_t ;

/* Variables and functions */

__attribute__((used)) static void _ccv_cnnp_cmd_exec_io_set_by(const ccv_nnc_tensor_symbol_t tensor_symbol, const ccv_cnnp_state_initializer_f initializer, void* const initializer_context, void* const context)
{
	const ccv_cnnp_cmd_exec_io_set_by_t* const set_by = (ccv_cnnp_cmd_exec_io_set_by_t*)context;
	initializer(initializer_context, set_by->cmd, set_by->hint, set_by->flags, 0, tensor_symbol);
}
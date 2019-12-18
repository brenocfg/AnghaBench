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
typedef  int /*<<< orphan*/  ccv_nnc_tensor_t ;
typedef  int /*<<< orphan*/  ccv_nnc_tensor_symbol_t ;
typedef  int /*<<< orphan*/  (* ccv_cnnp_state_initializer_f ) (void* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const) ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_DATA_TRANSFER_FORWARD () ; 
 int /*<<< orphan*/  ccv_nnc_no_hint ; 

__attribute__((used)) static void _ccv_cnnp_cmd_exec_io_copy(const ccv_nnc_tensor_symbol_t tensor_symbol, const ccv_cnnp_state_initializer_f initializer, void* const initializer_context, void* const context)
{
	initializer(initializer_context, CMD_DATA_TRANSFER_FORWARD(), ccv_nnc_no_hint, 0, (ccv_nnc_tensor_t*)context, tensor_symbol);
}
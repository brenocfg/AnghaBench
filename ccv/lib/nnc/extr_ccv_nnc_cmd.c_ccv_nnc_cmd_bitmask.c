#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {scalar_t__ cmd; } ;
typedef  TYPE_1__ ccv_nnc_cmd_t ;
struct TYPE_6__ {int (* bitmask ) (int const,int const,int /*<<< orphan*/  const* const,int const,int /*<<< orphan*/  const* const,int const) ;} ;
typedef  TYPE_2__ ccv_nnc_cmd_registry_t ;
struct TYPE_7__ {TYPE_2__ registry; } ;

/* Variables and functions */
 scalar_t__ CCV_NNC_CUSTOM_BACKWARD ; 
 scalar_t__ CCV_NNC_CUSTOM_FORWARD ; 
 scalar_t__ CCV_NNC_NOOP ; 
 int _ccv_nnc_cmd_ph (scalar_t__) ; 
 TYPE_3__* init_map ; 
 int stub1 (int const,int const,int /*<<< orphan*/  const* const,int const,int /*<<< orphan*/  const* const,int const) ; 

int ccv_nnc_cmd_bitmask(const ccv_nnc_cmd_t cmd, const int input_size, const int output_size, const uint64_t* const input_bitmasks, const int input_bitmask_size, const uint64_t* const output_bitmasks, const int output_bitmask_size)
{
	// If it is no-op, return true, it can deal with any number of parameters.
	if (cmd.cmd == CCV_NNC_NOOP)
		return 1;
	// If it is a custom command, I cannot check it at all, return false.
	if (cmd.cmd == CCV_NNC_CUSTOM_FORWARD || cmd.cmd == CCV_NNC_CUSTOM_BACKWARD)
		return 0;
	const int cmd_idx = _ccv_nnc_cmd_ph(cmd.cmd);
	const ccv_nnc_cmd_registry_t cmd_registry = init_map[cmd_idx].registry;
	if (cmd_registry.bitmask)
		return cmd_registry.bitmask(input_size, output_size, input_bitmasks, input_bitmask_size, output_bitmasks, output_bitmask_size);
	// If there is not checking, none can pass.
	return 0;
}
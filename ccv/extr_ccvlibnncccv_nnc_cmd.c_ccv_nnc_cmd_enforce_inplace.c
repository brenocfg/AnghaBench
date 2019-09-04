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
struct TYPE_5__ {scalar_t__ cmd; } ;
typedef  TYPE_1__ ccv_nnc_cmd_t ;
struct TYPE_6__ {int (* enforce_inplace ) (int const,int const,int const,int const) ;} ;
typedef  TYPE_2__ ccv_nnc_cmd_registry_t ;
struct TYPE_7__ {TYPE_2__ registry; } ;

/* Variables and functions */
 scalar_t__ CCV_NNC_CUSTOM_BACKWARD ; 
 scalar_t__ CCV_NNC_CUSTOM_FORWARD ; 
 scalar_t__ CCV_NNC_GRAPH_BACKWARD ; 
 scalar_t__ CCV_NNC_GRAPH_FORWARD ; 
 scalar_t__ CCV_NNC_NOOP ; 
 int _ccv_nnc_cmd_ph (scalar_t__) ; 
 TYPE_3__* init_map ; 
 int stub1 (int const,int const,int const,int const) ; 

int ccv_nnc_cmd_enforce_inplace(const ccv_nnc_cmd_t cmd, const int input_idx, const int input_size, const int output_idx, const int output_size)
{
	if (cmd.cmd == CCV_NNC_NOOP || cmd.cmd == CCV_NNC_CUSTOM_FORWARD || cmd.cmd == CCV_NNC_CUSTOM_BACKWARD || cmd.cmd == CCV_NNC_GRAPH_FORWARD || cmd.cmd == CCV_NNC_GRAPH_BACKWARD)
		return 0;
	const int cmd_idx = _ccv_nnc_cmd_ph(cmd.cmd);
	const ccv_nnc_cmd_registry_t registry = init_map[cmd_idx].registry;
	if (registry.enforce_inplace)
		return registry.enforce_inplace(input_idx, input_size, output_idx, output_size);
	return 0;
}
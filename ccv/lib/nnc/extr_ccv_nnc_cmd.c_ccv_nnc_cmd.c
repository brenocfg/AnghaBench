#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  ccv_nnc_cmd_vtab_t ;
struct TYPE_3__ {scalar_t__ cmd; int algorithm; int /*<<< orphan*/ * isa; int /*<<< orphan*/  backend; int /*<<< orphan*/  info; } ;
typedef  TYPE_1__ ccv_nnc_cmd_t ;
typedef  int /*<<< orphan*/  ccv_nnc_cmd_param_t ;

/* Variables and functions */
 scalar_t__ const CCV_NNC_CUSTOM_FORWARD ; 
 int /*<<< orphan*/  CCV_NNC_NO_BACKEND ; 
 int /*<<< orphan*/  assert (int) ; 

ccv_nnc_cmd_t ccv_nnc_cmd(const uint32_t _cmd, ccv_nnc_cmd_vtab_t* const isa, const ccv_nnc_cmd_param_t params, const int flags)
{
	ccv_nnc_cmd_t cmd;
	cmd.info = params;
	cmd.backend = CCV_NNC_NO_BACKEND;
	assert((_cmd == CCV_NNC_CUSTOM_FORWARD && isa) || (_cmd != CCV_NNC_CUSTOM_FORWARD && !isa));
	cmd.cmd = _cmd;
	cmd.algorithm = -1; // This is default.
	cmd.isa = isa;
	return cmd;
}
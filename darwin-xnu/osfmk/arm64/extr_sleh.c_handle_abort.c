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
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  fault_status_t ;
typedef  int /*<<< orphan*/  arm_saved_state_t ;
typedef  int /*<<< orphan*/  (* abort_inspector_t ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  (* abort_handler_t ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  ESR_ISS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
handle_abort(arm_saved_state_t *state, uint32_t esr, vm_offset_t fault_addr, vm_offset_t recover,
			 abort_inspector_t inspect_abort, abort_handler_t handler)
{
	fault_status_t		fault_code;
	vm_prot_t			fault_type;

	inspect_abort(ESR_ISS(esr), &fault_code, &fault_type);
	handler(state, esr, fault_addr, fault_code, fault_type, recover);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_prot_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  fault_status_t ;
struct TYPE_3__ {int /*<<< orphan*/  instr_ex_cnt; } ;
struct TYPE_4__ {TYPE_1__ cpu_stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISS_IA_FSC (int /*<<< orphan*/ ) ; 
 int VM_PROT_EXECUTE ; 
 int VM_PROT_READ ; 
 TYPE_2__* getCpuDatap () ; 

__attribute__((used)) static void
inspect_instruction_abort(uint32_t iss, fault_status_t *fault_code, vm_prot_t *fault_type)
{
	getCpuDatap()->cpu_stat.instr_ex_cnt++;
	*fault_code = ISS_IA_FSC(iss);
	*fault_type = (VM_PROT_READ | VM_PROT_EXECUTE);
}
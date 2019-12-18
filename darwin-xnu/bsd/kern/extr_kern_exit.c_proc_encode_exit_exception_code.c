#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  TYPE_1__* proc_t ;
typedef  int /*<<< orphan*/  mach_exception_data_type_t ;
struct TYPE_5__ {int /*<<< orphan*/  osr_code; int /*<<< orphan*/  osr_namespace; } ;
struct TYPE_4__ {TYPE_3__* p_exit_reason; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENCODE_OSR_CODE_TO_MACH_EXCEPTION_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENCODE_OSR_NAMESPACE_TO_MACH_EXCEPTION_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* OS_REASON_NULL ; 

mach_exception_data_type_t proc_encode_exit_exception_code(proc_t p)
{
	uint64_t subcode = 0;

	if (p->p_exit_reason == OS_REASON_NULL) {
		return 0;
	}

	/* Embed first 32 bits of osr_namespace and osr_code in exception code */
	ENCODE_OSR_NAMESPACE_TO_MACH_EXCEPTION_CODE(subcode, p->p_exit_reason->osr_namespace);
	ENCODE_OSR_CODE_TO_MACH_EXCEPTION_CODE(subcode, p->p_exit_reason->osr_code);
	return (mach_exception_data_type_t)subcode;
}
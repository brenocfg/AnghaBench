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
typedef  int /*<<< orphan*/  voucher_mach_msg_state_t ;
struct TYPE_2__ {void (* voucher_mach_msg_revert ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* _libkernel_voucher_functions ; 
 void stub1 (int /*<<< orphan*/ ) ; 

void
voucher_mach_msg_revert(voucher_mach_msg_state_t state)
{
	if (_libkernel_voucher_functions->voucher_mach_msg_revert) {
		return _libkernel_voucher_functions->voucher_mach_msg_revert(state);
	}
}
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
typedef  int /*<<< orphan*/  mach_msg_header_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* voucher_mach_msg_adopt ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VOUCHER_MACH_MSG_STATE_UNCHANGED ; 
 TYPE_1__* _libkernel_voucher_functions ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

voucher_mach_msg_state_t
voucher_mach_msg_adopt(mach_msg_header_t *msg)
{
	if (_libkernel_voucher_functions->voucher_mach_msg_adopt) {
		return _libkernel_voucher_functions->voucher_mach_msg_adopt(msg);
	}
	return VOUCHER_MACH_MSG_STATE_UNCHANGED;
}
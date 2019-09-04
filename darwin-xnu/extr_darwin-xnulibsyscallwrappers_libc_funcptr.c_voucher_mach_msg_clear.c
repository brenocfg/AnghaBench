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
typedef  int /*<<< orphan*/  mach_msg_header_t ;
struct TYPE_2__ {void (* voucher_mach_msg_clear ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_1__* _libkernel_voucher_functions ; 
 void stub1 (int /*<<< orphan*/ *) ; 

void
voucher_mach_msg_clear(mach_msg_header_t *msg)
{
	if (_libkernel_voucher_functions->voucher_mach_msg_clear) {
		return _libkernel_voucher_functions->voucher_mach_msg_clear(msg);
	}
}
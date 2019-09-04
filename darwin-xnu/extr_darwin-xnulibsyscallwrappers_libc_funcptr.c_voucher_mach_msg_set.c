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
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* voucher_mach_msg_set ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_1__* _libkernel_voucher_functions ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

boolean_t
voucher_mach_msg_set(mach_msg_header_t *msg)
{
	if (_libkernel_voucher_functions->voucher_mach_msg_set) {
		return _libkernel_voucher_functions->voucher_mach_msg_set(msg);
	}
	return 0;
}
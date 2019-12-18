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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  mach_msg_header_t ;

/* Variables and functions */
 int proc_importance_assertion_begin_with_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
proc_denap_assertion_begin_with_msg(mach_msg_header_t  *msg,
				    uint64_t           *assertion_token)
{
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
	return proc_importance_assertion_begin_with_msg(msg, NULL, assertion_token);
#pragma clang diagnostic pop
}
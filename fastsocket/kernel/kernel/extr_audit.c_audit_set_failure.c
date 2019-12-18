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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int AUDIT_FAIL_PANIC ; 
 int AUDIT_FAIL_PRINTK ; 
 int AUDIT_FAIL_SILENT ; 
 int EINVAL ; 
 int audit_do_config_change (char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_failure ; 

__attribute__((used)) static int audit_set_failure(int state, uid_t loginuid, u32 sessionid, u32 sid)
{
	if (state != AUDIT_FAIL_SILENT
	    && state != AUDIT_FAIL_PRINTK
	    && state != AUDIT_FAIL_PANIC)
		return -EINVAL;

	return audit_do_config_change("audit_failure", &audit_failure, state,
				      loginuid, sessionid, sid);
}
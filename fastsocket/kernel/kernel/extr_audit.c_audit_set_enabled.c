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
 int AUDIT_LOCKED ; 
 int AUDIT_OFF ; 
 int EINVAL ; 
 int audit_do_config_change (char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_enabled ; 
 int audit_ever_enabled ; 

__attribute__((used)) static int audit_set_enabled(int state, uid_t loginuid, u32 sessionid, u32 sid)
{
	int rc;
	if (state < AUDIT_OFF || state > AUDIT_LOCKED)
		return -EINVAL;

	rc =  audit_do_config_change("audit_enabled", &audit_enabled, state,
				     loginuid, sessionid, sid);

	if (!rc)
		audit_ever_enabled |= !!state;

	return rc;
}
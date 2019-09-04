#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* val; } ;
typedef  TYPE_1__ audit_token_t ;

/* Variables and functions */

int
get_audit_token_pid(audit_token_t *audit_token)
{
	/* keep in-sync with set_security_token (above) */
	if (audit_token)
		return (int)audit_token->val[5];
	return -1;
}
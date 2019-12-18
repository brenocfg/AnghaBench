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
struct audit_session_self_args {int dummy; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;

/* Variables and functions */
 int ENOSYS ; 

int
audit_session_self(proc_t p, struct audit_session_self_args *uap,
    mach_port_name_t *ret_port)
{
#pragma unused(p, uap, ret_port)

	return (ENOSYS);
}
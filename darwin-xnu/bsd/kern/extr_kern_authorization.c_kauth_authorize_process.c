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
struct proc {int dummy; } ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
typedef  int /*<<< orphan*/  kauth_action_t ;

/* Variables and functions */
 int kauth_authorize_action (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t,uintptr_t,uintptr_t,uintptr_t) ; 
 int /*<<< orphan*/  kauth_scope_process ; 

int
kauth_authorize_process(kauth_cred_t credential, kauth_action_t action, struct proc *process, uintptr_t arg1, uintptr_t arg2, uintptr_t arg3)
{
	return(kauth_authorize_action(kauth_scope_process, credential, action, (uintptr_t)process, arg1, arg2, arg3));
}
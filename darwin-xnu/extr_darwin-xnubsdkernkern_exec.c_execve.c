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
struct execve_args {int /*<<< orphan*/  envp; int /*<<< orphan*/  argp; int /*<<< orphan*/  fname; } ;
struct __mac_execve_args {int /*<<< orphan*/  mac_p; int /*<<< orphan*/  envp; int /*<<< orphan*/  argp; int /*<<< orphan*/  fname; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC_NONE ; 
 int /*<<< orphan*/  USER_ADDR_NULL ; 
 int /*<<< orphan*/  VM_EXECVE ; 
 int __mac_execve (int /*<<< orphan*/ ,struct __mac_execve_args*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memoryshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
execve(proc_t p, struct execve_args *uap, int32_t *retval)
{
	struct __mac_execve_args muap;
	int err;

	memoryshot(VM_EXECVE, DBG_FUNC_NONE);

	muap.fname = uap->fname;
	muap.argp = uap->argp;
	muap.envp = uap->envp;
	muap.mac_p = USER_ADDR_NULL;
	err = __mac_execve(p, &muap, retval);

	return(err);
}
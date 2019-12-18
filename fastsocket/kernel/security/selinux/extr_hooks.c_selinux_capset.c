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
struct cred {int dummy; } ;
typedef  int /*<<< orphan*/  kernel_cap_t ;

/* Variables and functions */
 int /*<<< orphan*/  PROCESS__SETCAP ; 
 int cap_capset (struct cred*,struct cred const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int cred_has_perm (struct cred const*,struct cred*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int selinux_capset(struct cred *new, const struct cred *old,
			  const kernel_cap_t *effective,
			  const kernel_cap_t *inheritable,
			  const kernel_cap_t *permitted)
{
	int error;

	error = cap_capset(new, old,
				      effective, inheritable, permitted);
	if (error)
		return error;

	return cred_has_perm(old, new, PROCESS__SETCAP);
}
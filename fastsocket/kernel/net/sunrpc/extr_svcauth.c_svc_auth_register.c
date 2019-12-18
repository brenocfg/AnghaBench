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
struct auth_ops {int dummy; } ;
typedef  size_t rpc_authflavor_t ;

/* Variables and functions */
 int EINVAL ; 
 size_t RPC_AUTH_MAXFLAVOR ; 
 struct auth_ops** authtab ; 
 int /*<<< orphan*/  authtab_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int
svc_auth_register(rpc_authflavor_t flavor, struct auth_ops *aops)
{
	int rv = -EINVAL;
	spin_lock(&authtab_lock);
	if (flavor < RPC_AUTH_MAXFLAVOR && authtab[flavor] == NULL) {
		authtab[flavor] = aops;
		rv = 0;
	}
	spin_unlock(&authtab_lock);
	return rv;
}
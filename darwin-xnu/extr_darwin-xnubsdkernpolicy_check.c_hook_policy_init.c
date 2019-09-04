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
struct mac_policy_conf {char* mpc_name; char* mpc_fullname; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*,char*) ; 

__attribute__((used)) static void
hook_policy_init(struct mac_policy_conf *mpc)
{
	printf("Policy '%s' = '%s' ready\n", mpc->mpc_name, mpc->mpc_fullname);
}
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
struct mac_policy_conf {char* mpc_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void
hook_policy_initbsd(struct mac_policy_conf *mpc)
{
	/* called with policy_grab_exclusive mutex held; exempt */
	printf("hook_policy_initbsd: %s\n", mpc->mpc_name);
}
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
typedef  int /*<<< orphan*/  kauth_cred_t ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 scalar_t__ kauth_cred_ismember_gid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

int
groupmember(gid_t gid, kauth_cred_t cred)
{
	int is_member;

	if (kauth_cred_ismember_gid(cred, gid, &is_member) == 0 && is_member)
		return (1);
	return (0);
}
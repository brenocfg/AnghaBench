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
typedef  int /*<<< orphan*/  u32 ;
struct cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SECCLASS_PROCESS ; 
 int avc_has_perm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cred_sid (struct cred const*) ; 

__attribute__((used)) static int cred_has_perm(const struct cred *actor,
			 const struct cred *target,
			 u32 perms)
{
	u32 asid = cred_sid(actor), tsid = cred_sid(target);

	return avc_has_perm(asid, tsid, SECCLASS_PROCESS, perms, NULL);
}
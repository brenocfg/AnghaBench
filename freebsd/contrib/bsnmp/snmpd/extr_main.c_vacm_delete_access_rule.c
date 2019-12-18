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
struct vacm_access {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct vacm_access*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct vacm_access*) ; 
 int /*<<< orphan*/  vacm_accesslist ; 
 int /*<<< orphan*/  vva ; 

int
vacm_delete_access_rule(struct vacm_access *acl)
{
	TAILQ_REMOVE(&vacm_accesslist, acl, vva);
	free(acl);

	return (0);
}
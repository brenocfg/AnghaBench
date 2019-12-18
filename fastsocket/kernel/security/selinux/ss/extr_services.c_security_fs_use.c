#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_5__ {unsigned int behavior; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct ocontext {scalar_t__* sid; int /*<<< orphan*/ * context; TYPE_2__ v; struct ocontext* next; TYPE_1__ u; } ;
struct TYPE_6__ {struct ocontext** ocontexts; } ;

/* Variables and functions */
 size_t OCON_FSUSE ; 
 int /*<<< orphan*/  SECCLASS_DIR ; 
 unsigned int SECURITY_FS_USE_GENFS ; 
 unsigned int SECURITY_FS_USE_NONE ; 
 int /*<<< orphan*/  policy_rwlock ; 
 TYPE_3__ policydb ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int security_genfs_sid (char const*,char*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  sidtab ; 
 int sidtab_context_to_sid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

int security_fs_use(
	const char *fstype,
	unsigned int *behavior,
	u32 *sid)
{
	int rc = 0;
	struct ocontext *c;

	read_lock(&policy_rwlock);

	c = policydb.ocontexts[OCON_FSUSE];
	while (c) {
		if (strcmp(fstype, c->u.name) == 0)
			break;
		c = c->next;
	}

	if (c) {
		*behavior = c->v.behavior;
		if (!c->sid[0]) {
			rc = sidtab_context_to_sid(&sidtab,
						   &c->context[0],
						   &c->sid[0]);
			if (rc)
				goto out;
		}
		*sid = c->sid[0];
	} else {
		rc = security_genfs_sid(fstype, "/", SECCLASS_DIR, sid);
		if (rc) {
			*behavior = SECURITY_FS_USE_NONE;
			rc = 0;
		} else {
			*behavior = SECURITY_FS_USE_GENFS;
		}
	}

out:
	read_unlock(&policy_rwlock);
	return rc;
}
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
typedef  scalar_t__ u16 ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {scalar_t__ sclass; } ;
struct ocontext {scalar_t__* sid; int /*<<< orphan*/ * context; TYPE_2__ u; TYPE_1__ v; struct ocontext* next; } ;
struct genfs {struct ocontext* head; int /*<<< orphan*/  fstype; struct genfs* next; } ;
struct TYPE_6__ {struct genfs* genfs; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ SECINITSID_UNLABELED ; 
 int /*<<< orphan*/  policy_rwlock ; 
 TYPE_3__ policydb ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sidtab ; 
 int sidtab_context_to_sid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int strcmp (char const*,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ unmap_class (scalar_t__) ; 

int security_genfs_sid(const char *fstype,
		       char *path,
		       u16 orig_sclass,
		       u32 *sid)
{
	int len;
	u16 sclass;
	struct genfs *genfs;
	struct ocontext *c;
	int rc = 0, cmp = 0;

	while (path[0] == '/' && path[1] == '/')
		path++;

	read_lock(&policy_rwlock);

	sclass = unmap_class(orig_sclass);

	for (genfs = policydb.genfs; genfs; genfs = genfs->next) {
		cmp = strcmp(fstype, genfs->fstype);
		if (cmp <= 0)
			break;
	}

	if (!genfs || cmp) {
		*sid = SECINITSID_UNLABELED;
		rc = -ENOENT;
		goto out;
	}

	for (c = genfs->head; c; c = c->next) {
		len = strlen(c->u.name);
		if ((!c->v.sclass || sclass == c->v.sclass) &&
		    (strncmp(c->u.name, path, len) == 0))
			break;
	}

	if (!c) {
		*sid = SECINITSID_UNLABELED;
		rc = -ENOENT;
		goto out;
	}

	if (!c->sid[0]) {
		rc = sidtab_context_to_sid(&sidtab,
					   &c->context[0],
					   &c->sid[0]);
		if (rc)
			goto out;
	}

	*sid = c->sid[0];
out:
	read_unlock(&policy_rwlock);
	return rc;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct ocontext {scalar_t__* sid; int /*<<< orphan*/ * context; struct ocontext* next; TYPE_1__ u; } ;
struct TYPE_4__ {struct ocontext** ocontexts; } ;

/* Variables and functions */
 size_t OCON_NETIF ; 
 scalar_t__ SECINITSID_NETIF ; 
 int /*<<< orphan*/  policy_rwlock ; 
 TYPE_2__ policydb ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sidtab ; 
 int sidtab_context_to_sid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

int security_netif_sid(char *name, u32 *if_sid)
{
	int rc = 0;
	struct ocontext *c;

	read_lock(&policy_rwlock);

	c = policydb.ocontexts[OCON_NETIF];
	while (c) {
		if (strcmp(name, c->u.name) == 0)
			break;
		c = c->next;
	}

	if (c) {
		if (!c->sid[0] || !c->sid[1]) {
			rc = sidtab_context_to_sid(&sidtab,
						  &c->context[0],
						  &c->sid[0]);
			if (rc)
				goto out;
			rc = sidtab_context_to_sid(&sidtab,
						   &c->context[1],
						   &c->sid[1]);
			if (rc)
				goto out;
		}
		*if_sid = c->sid[0];
	} else
		*if_sid = SECINITSID_NETIF;

out:
	read_unlock(&policy_rwlock);
	return rc;
}
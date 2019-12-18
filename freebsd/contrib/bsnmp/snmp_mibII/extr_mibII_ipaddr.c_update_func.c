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
struct update {int set; int rb; int /*<<< orphan*/  addr; int /*<<< orphan*/  rb_bcast; int /*<<< orphan*/  rb_mask; int /*<<< orphan*/  ifindex; } ;
struct snmp_dependency {int dummy; } ;
struct snmp_context {int dummy; } ;
struct mibifa {int flags; int /*<<< orphan*/  inbcast; int /*<<< orphan*/  inmask; } ;
typedef  enum snmp_depop { ____Placeholder_snmp_depop } snmp_depop ;

/* Variables and functions */
 int MIBIFA_DESTROYED ; 
 int RB_CREATE ; 
 int RB_DESTROY ; 
 int RB_MODIFY ; 
#define  SNMP_DEPOP_COMMIT 130 
#define  SNMP_DEPOP_FINISH 129 
#define  SNMP_DEPOP_ROLLBACK 128 
 int SNMP_ERR_INCONS_NAME ; 
 int SNMP_ERR_NOERROR ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct mibifa*,int /*<<< orphan*/ ) ; 
 int UPD_IFINDEX ; 
 int /*<<< orphan*/  abort () ; 
 int create (struct update*) ; 
 int destroy (struct snmp_context*,struct update*,struct mibifa*) ; 
 int /*<<< orphan*/  free (struct mibifa*) ; 
 int /*<<< orphan*/  link ; 
 struct mibifa* mib_find_ifa (int /*<<< orphan*/ ) ; 
 int mib_iflist_bad ; 
 int /*<<< orphan*/  mib_uncreate_ifa (struct mibifa*) ; 
 int /*<<< orphan*/  mib_undestroy_ifa (struct mibifa*) ; 
 int /*<<< orphan*/  mib_unmodify_ifa (struct mibifa*) ; 
 int /*<<< orphan*/  mibifa_list ; 
 int modify (struct update*,struct mibifa*) ; 

__attribute__((used)) static int
update_func(struct snmp_context *ctx, struct snmp_dependency *dep,
    enum snmp_depop op)
{
	struct update *upd = (struct update *)dep;
	struct mibifa *ifa;

	switch (op) {

	  case SNMP_DEPOP_COMMIT:
		if ((ifa = mib_find_ifa(upd->addr)) == NULL) {
			/* non existing entry - must have ifindex */
			if (!(upd->set & UPD_IFINDEX))
				return (SNMP_ERR_INCONS_NAME);
			return (create(upd));
		}
		/* existing entry */
		if ((upd->set & UPD_IFINDEX) && upd->ifindex == 0) {
			/* delete */
			return (destroy(ctx, upd, ifa));
		}
		/* modify entry */
		return (modify(upd, ifa));

	  case SNMP_DEPOP_ROLLBACK:
		if ((ifa = mib_find_ifa(upd->addr)) == NULL) {
			/* ups */
			mib_iflist_bad = 1;
			return (SNMP_ERR_NOERROR);
		}
		if (upd->rb & RB_CREATE) {
			mib_uncreate_ifa(ifa);
			return (SNMP_ERR_NOERROR);
		}
		if (upd->rb & RB_DESTROY) {
			mib_undestroy_ifa(ifa);
			return (SNMP_ERR_NOERROR);
		}
		if (upd->rb & RB_MODIFY) {
			ifa->inmask = upd->rb_mask;
			ifa->inbcast = upd->rb_bcast;
			mib_unmodify_ifa(ifa);
			return (SNMP_ERR_NOERROR);
		}
		return (SNMP_ERR_NOERROR);

	  case SNMP_DEPOP_FINISH:
		if ((upd->rb & RB_DESTROY) &&
		    (ifa = mib_find_ifa(upd->addr)) != NULL &&
		    (ifa->flags & MIBIFA_DESTROYED)) {
			TAILQ_REMOVE(&mibifa_list, ifa, link);
			free(ifa);
		}
		return (SNMP_ERR_NOERROR);
	}
	abort();
}
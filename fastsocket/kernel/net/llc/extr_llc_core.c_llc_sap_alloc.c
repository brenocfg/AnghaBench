#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct llc_sap {int /*<<< orphan*/  refcnt; TYPE_1__ sk_list; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  LLC_SAP_STATE_ACTIVE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct llc_sap* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct llc_sap *llc_sap_alloc(void)
{
	struct llc_sap *sap = kzalloc(sizeof(*sap), GFP_ATOMIC);

	if (sap) {
		/* sap->laddr.mac - leave as a null, it's filled by bind */
		sap->state = LLC_SAP_STATE_ACTIVE;
		rwlock_init(&sap->sk_list.lock);
		atomic_set(&sap->refcnt, 1);
	}
	return sap;
}
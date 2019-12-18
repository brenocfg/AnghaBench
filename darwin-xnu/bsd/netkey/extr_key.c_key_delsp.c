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
struct TYPE_2__ {int /*<<< orphan*/ * internal_if; } ;
struct secpolicy {scalar_t__ refcnt; struct ipsecrequest* req; int /*<<< orphan*/ * outgoing_if; int /*<<< orphan*/ * ipsec_if; TYPE_1__ spidx; int /*<<< orphan*/  state; } ;
struct ipsecrequest {struct ipsecrequest* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPSEC_SPSTATE_DEAD ; 
 int /*<<< orphan*/  KFREE (struct ipsecrequest*) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  LIST_REMOVE (struct secpolicy*,int /*<<< orphan*/ ) ; 
 scalar_t__ __LIST_CHAINED (struct secpolicy*) ; 
 int /*<<< orphan*/  chain ; 
 int /*<<< orphan*/  ifnet_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipsec_policy_count ; 
 int /*<<< orphan*/  keydb_delsecpolicy (struct secpolicy*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  sadb_mutex ; 

__attribute__((used)) static void
key_delsp(
		  struct secpolicy *sp)
{
	
	/* sanity check */
	if (sp == NULL)
		panic("key_delsp: NULL pointer is passed.\n");
	
	LCK_MTX_ASSERT(sadb_mutex, LCK_MTX_ASSERT_OWNED);
	sp->state = IPSEC_SPSTATE_DEAD;
	
	if (sp->refcnt > 0)
		return; /* can't free */
	
	/* remove from SP index */
	if (__LIST_CHAINED(sp)) {
		LIST_REMOVE(sp, chain);
		ipsec_policy_count--;
	}
	
    if (sp->spidx.internal_if) {
        ifnet_release(sp->spidx.internal_if);
        sp->spidx.internal_if = NULL;
    }
    
    if (sp->ipsec_if) {
        ifnet_release(sp->ipsec_if);
        sp->ipsec_if = NULL;
    }
    
    if (sp->outgoing_if) {
        ifnet_release(sp->outgoing_if);
        sp->outgoing_if = NULL;
    }
	
    {
		struct ipsecrequest *isr = sp->req, *nextisr;
		
		while (isr != NULL) {
			nextisr = isr->next;
			KFREE(isr);
			isr = nextisr;
    	}
	}
	keydb_delsecpolicy(sp);
	
	return;
}
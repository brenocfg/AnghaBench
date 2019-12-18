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
typedef  size_t u_int ;
struct secasvar {scalar_t__ refcnt; int /*<<< orphan*/ * sah; int /*<<< orphan*/  state; } ;
struct secashead {struct secashead* identd; struct secashead* idents; int /*<<< orphan*/ * ipsec_if; int /*<<< orphan*/  sa_route; int /*<<< orphan*/ * savtree; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_CHKSASTATE (size_t,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  KEY_SADB_LOCKED ; 
 int /*<<< orphan*/  KFREE (struct secashead*) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 scalar_t__ LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct secasvar* LIST_NEXT (struct secasvar*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct secashead*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ROUTE_RELEASE (int /*<<< orphan*/ *) ; 
 size_t _ARRAYLEN (size_t*) ; 
 scalar_t__ __LIST_CHAINED (struct secashead*) ; 
 int /*<<< orphan*/  chain ; 
 int /*<<< orphan*/  ifnet_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_freesav (struct secasvar*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  sadb_mutex ; 
 size_t* saorder_state_any ; 

void
key_delsah(
		   struct secashead *sah)
{
	struct secasvar *sav, *nextsav;
	u_int stateidx, state;
	int zombie = 0;
	
	LCK_MTX_ASSERT(sadb_mutex, LCK_MTX_ASSERT_OWNED);
	
	/* sanity check */
	if (sah == NULL)
		panic("key_delsah: NULL pointer is passed.\n");
	
	/* searching all SA registerd in the secindex. */
	for (stateidx = 0;
	     stateidx < _ARRAYLEN(saorder_state_any);
	     stateidx++) {
		
		state = saorder_state_any[stateidx];
		for (sav = (struct secasvar *)LIST_FIRST(&sah->savtree[state]);
		     sav != NULL;
		     sav = nextsav) {
			
			nextsav = LIST_NEXT(sav, chain);
			
			if (sav->refcnt > 0) {
				/* give up to delete this sa */
				zombie++;
				continue;
			}
			
			/* sanity check */
			KEY_CHKSASTATE(state, sav->state, "key_delsah");
			
			key_freesav(sav, KEY_SADB_LOCKED);
			
			/* remove back pointer */
			sav->sah = NULL;
			sav = NULL;
		}
	}
	
	/* don't delete sah only if there are savs. */
	if (zombie)
		return;
	
	ROUTE_RELEASE(&sah->sa_route);
    
	if (sah->ipsec_if) {
		ifnet_release(sah->ipsec_if);
		sah->ipsec_if = NULL;
	}
	
    if (sah->idents) {
        KFREE(sah->idents);
    }
    
    if (sah->identd) {
        KFREE(sah->identd);
    }
	
	/* remove from tree of SA index */
	if (__LIST_CHAINED(sah))
		LIST_REMOVE(sah, chain);
	
	KFREE(sah);
	
	return;
}
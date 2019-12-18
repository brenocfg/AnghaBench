#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ifbond_ref ;
typedef  int UInt32 ;
struct TYPE_8__ {int /*<<< orphan*/  ifma_addr; int /*<<< orphan*/  ifma_ifp; } ;
struct TYPE_7__ {int /*<<< orphan*/  verbose; } ;
struct TYPE_6__ {char* ifb_name; int /*<<< orphan*/ * ifb_distributing_array; TYPE_5__* ifb_ifma_slow_proto; int /*<<< orphan*/  ifb_retain_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFMA_REMREF (TYPE_5__*) ; 
 int /*<<< orphan*/  M_BOND ; 
 int OSDecrementAtomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bond_cloner ; 
 TYPE_4__* g_bond ; 
 int /*<<< orphan*/  if_clone_softc_deallocate (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  if_delmulti_anon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static __inline__ void
ifbond_release(ifbond_ref ifb)
{
    UInt32		old_retain_count;

    old_retain_count = OSDecrementAtomic(&ifb->ifb_retain_count);
    switch (old_retain_count) {
    case 0:
	panic("ifbond_release: retain count is 0\n");
	break;
    case 1:
	if (g_bond->verbose) {
	    printf("ifbond_release(%s)\n", ifb->ifb_name);
	}
	if (ifb->ifb_ifma_slow_proto != NULL) {
	    if (g_bond->verbose) {
		printf("ifbond_release(%s) removing multicast\n",
		       ifb->ifb_name);
	    }
	    (void) if_delmulti_anon(ifb->ifb_ifma_slow_proto->ifma_ifp,
	        ifb->ifb_ifma_slow_proto->ifma_addr);
	    IFMA_REMREF(ifb->ifb_ifma_slow_proto);
	}
	if (ifb->ifb_distributing_array != NULL) {
	    FREE(ifb->ifb_distributing_array, M_BOND);
	}
	if_clone_softc_deallocate(&bond_cloner, ifb);
	break;
    default:
	break;
    }
    return;
}
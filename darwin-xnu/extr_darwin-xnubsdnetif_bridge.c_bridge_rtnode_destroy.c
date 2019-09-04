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
struct bridge_softc {int /*<<< orphan*/  sc_brtcnt; } ;
struct bridge_rtnode {TYPE_1__* brt_dst; } ;
struct TYPE_2__ {int /*<<< orphan*/  bif_addrcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRIDGE_LOCK_ASSERT_HELD (struct bridge_softc*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct bridge_rtnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bridge_rtnode_pool ; 
 int /*<<< orphan*/  brt_hash ; 
 int /*<<< orphan*/  brt_list ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,struct bridge_rtnode*) ; 

__attribute__((used)) static void
bridge_rtnode_destroy(struct bridge_softc *sc, struct bridge_rtnode *brt)
{
	BRIDGE_LOCK_ASSERT_HELD(sc);

	LIST_REMOVE(brt, brt_hash);

	LIST_REMOVE(brt, brt_list);
	sc->sc_brtcnt--;
	brt->brt_dst->bif_addrcnt--;
	zfree(bridge_rtnode_pool, brt);
}
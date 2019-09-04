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
struct bridge_softc {int /*<<< orphan*/  sc_brtcnt; int /*<<< orphan*/  sc_rtlist; } ;
struct bridge_rtnode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct bridge_rtnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bridge_rthash_resize (struct bridge_softc*) ; 
 int bridge_rtnode_hash (struct bridge_softc*,struct bridge_rtnode*) ; 
 int /*<<< orphan*/  brt_list ; 

__attribute__((used)) static int
bridge_rtnode_insert(struct bridge_softc *sc, struct bridge_rtnode *brt)
{
	int error;

	error = bridge_rtnode_hash(sc, brt);
	if (error != 0)
		return (error);

	LIST_INSERT_HEAD(&sc->sc_rtlist, brt, brt_list);
	sc->sc_brtcnt++;

	bridge_rthash_resize(sc);

	return (0);
}
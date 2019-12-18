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
struct ifnet {struct gif_softc* if_softc; } ;
struct gif_softc {int /*<<< orphan*/  gif_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  gif_cloner ; 
 int /*<<< orphan*/  gif_mtx_grp ; 
 int /*<<< orphan*/  if_clone_softc_deallocate (int /*<<< orphan*/ *,struct gif_softc*) ; 
 int /*<<< orphan*/  ifnet_release (struct ifnet*) ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gif_detach(struct ifnet *ifp)
{
	struct gif_softc *sc = ifp->if_softc;
	lck_mtx_destroy(&sc->gif_lock, gif_mtx_grp);
	if_clone_softc_deallocate(&gif_cloner, sc);
	ifp->if_softc = NULL;
	(void) ifnet_release(ifp);
}
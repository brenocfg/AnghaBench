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
struct gif_softc {int gif_flags; int /*<<< orphan*/ * encap_cookie4; int /*<<< orphan*/ * encap_cookie6; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GIF_LOCK (struct gif_softc*) ; 
 int /*<<< orphan*/  GIF_UNLOCK (struct gif_softc*) ; 
 int IFGIF_DETACHING ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct gif_softc*,int /*<<< orphan*/ ) ; 
 int encap_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gif_delete_tunnel (struct gif_softc*) ; 
 int /*<<< orphan*/  gif_link ; 
 int /*<<< orphan*/  gif_mtx ; 
 int /*<<< orphan*/  gifs ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngif ; 

__attribute__((used)) static int
gif_remove(struct ifnet *ifp)
{
	int error = 0;
	struct gif_softc *sc = NULL;

	lck_mtx_lock(gif_mtx);
	sc = ifp->if_softc;

	if (sc == NULL) {
		error = EINVAL;
		goto done;
	}

	GIF_LOCK(sc);
	if (sc->gif_flags & IFGIF_DETACHING) {
		error = EINVAL;
		goto done;
	}

	sc->gif_flags |= IFGIF_DETACHING;
	TAILQ_REMOVE(&gifs, sc, gif_link);
	ngif--;

	gif_delete_tunnel(sc);
#ifdef INET6
	if (sc->encap_cookie6 != NULL) {
		error = encap_detach(sc->encap_cookie6);
		KASSERT(error == 0, ("gif_clone_destroy: Unexpected "
		    "error detaching encap_cookie6"));
	}
#endif
#ifdef INET
	if (sc->encap_cookie4 != NULL) {
		error = encap_detach(sc->encap_cookie4);
		KASSERT(error == 0, ("gif_clone_destroy: Unexpected "
		    "error detaching encap_cookie4"));
	}
#endif
done:
	if (sc != NULL)
		GIF_UNLOCK(sc);
	lck_mtx_unlock(gif_mtx);

	return (error);
}
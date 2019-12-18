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
struct gif_softc {int /*<<< orphan*/  gif_ro; int /*<<< orphan*/ * gif_pdst; int /*<<< orphan*/ * gif_psrc; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIF_LOCK_ASSERT (struct gif_softc*) ; 
 int /*<<< orphan*/  M_IFADDR ; 
 int /*<<< orphan*/  ROUTE_RELEASE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gif_delete_tunnel(struct gif_softc *sc)
{
	GIF_LOCK_ASSERT(sc);
	if (sc->gif_psrc) {
		FREE((caddr_t)sc->gif_psrc, M_IFADDR);
		sc->gif_psrc = NULL;
	}
	if (sc->gif_pdst) {
		FREE((caddr_t)sc->gif_pdst, M_IFADDR);
		sc->gif_pdst = NULL;
	}
	ROUTE_RELEASE(&sc->gif_ro);
	/* change the IFF_UP flag as well? */
}
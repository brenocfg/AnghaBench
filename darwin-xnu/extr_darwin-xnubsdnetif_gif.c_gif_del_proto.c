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
struct gif_softc {scalar_t__ gif_proto; } ;
typedef  scalar_t__ protocol_family_t ;
typedef  int /*<<< orphan*/  ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  GIF_LOCK (struct gif_softc*) ; 
 int /*<<< orphan*/  GIF_UNLOCK (struct gif_softc*) ; 
 struct gif_softc* ifnet_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static errno_t
gif_del_proto(
	ifnet_t ifp,
	protocol_family_t protocol_family)
{
	struct gif_softc *sc = ifnet_softc(ifp);

	GIF_LOCK(sc);
	if (sc->gif_proto == protocol_family)
		sc->gif_proto = 0;
	GIF_UNLOCK(sc);

	return (0);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int sa_family; } ;
struct gif_softc {int /*<<< orphan*/  gif_proto; struct sockaddr* gif_psrc; struct sockaddr* gif_pdst; } ;
typedef  TYPE_2__* mbuf_t ;
typedef  int /*<<< orphan*/  ifnet_t ;
typedef  int errno_t ;
struct TYPE_8__ {int /*<<< orphan*/  len; } ;
struct TYPE_9__ {int m_flags; TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int EJUSTRETURN ; 
 int ENETDOWN ; 
 int /*<<< orphan*/  GIF_LOCK (struct gif_softc*) ; 
 int /*<<< orphan*/  GIF_UNLOCK (struct gif_softc*) ; 
 int IFF_UP ; 
 int M_BCAST ; 
 int M_MCAST ; 
 int /*<<< orphan*/  bpf_tap_out (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int ifnet_flags (int /*<<< orphan*/ ) ; 
 struct gif_softc* ifnet_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_stat_increment_out (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ifnet_touch_lastchange (int /*<<< orphan*/ ) ; 
 int in6_gif_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int in_gif_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (TYPE_2__*) ; 

__attribute__((used)) static errno_t
gif_output(
	ifnet_t ifp,
	mbuf_t m)
{
	struct gif_softc *sc = ifnet_softc(ifp);
	struct sockaddr *gif_psrc;
	struct sockaddr *gif_pdst;
	int error = 0;

	GIF_LOCK(sc);
	gif_psrc = sc->gif_psrc;
	gif_pdst = sc->gif_pdst;
	GIF_UNLOCK(sc);

	/*
	 * max_gif_nesting check used to live here. It doesn't anymore
	 * because there is no guaruntee that we won't be called
	 * concurrently from more than one thread.
	 */
	m->m_flags &= ~(M_BCAST|M_MCAST);
	if (!(ifnet_flags(ifp) & IFF_UP) ||
	    gif_psrc == NULL || gif_pdst == NULL) {
		ifnet_touch_lastchange(ifp);
		m_freem(m);	/* free it here not in dlil_output */
		error = ENETDOWN;
		goto end;
	}

	bpf_tap_out(ifp, 0, m, &sc->gif_proto, sizeof (sc->gif_proto));

	GIF_LOCK(sc);

	/* inner AF-specific encapsulation */

	/* XXX should we check if our outer source is legal? */

	/* dispatch to output logic based on outer AF */
	switch (sc->gif_psrc->sa_family) {
#if INET
	case AF_INET:
		error = in_gif_output(ifp, sc->gif_proto, m, NULL);
		break;
#endif
#if INET6
	case AF_INET6:
		error = in6_gif_output(ifp, sc->gif_proto, m, NULL);
		break;
#endif
	default:
		error = ENETDOWN;
		break;
	}

	GIF_UNLOCK(sc);
end:        
	if (error) {
		/* the mbuf was freed either by in_gif_output or in here */
		ifnet_stat_increment_out(ifp, 0, 0, 1);
	} else {
		ifnet_stat_increment_out(ifp, 1, m->m_pkthdr.len, 0);
	}
	if (error == 0)
		error = EJUSTRETURN; /* if no error, packet got sent already */
	return (error);
}
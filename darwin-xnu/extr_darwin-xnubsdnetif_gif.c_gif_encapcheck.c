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
struct mbuf {int dummy; } ;
struct ip {int ip_v; } ;
struct gif_softc {int /*<<< orphan*/  gif_pdst; int /*<<< orphan*/  gif_psrc; int /*<<< orphan*/  gif_if; } ;
typedef  int /*<<< orphan*/  ip ;

/* Variables and functions */
 int /*<<< orphan*/  GIF_LOCK (struct gif_softc*) ; 
 int /*<<< orphan*/  GIF_UNLOCK (struct gif_softc*) ; 
 int IFF_UP ; 
 int ifnet_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbuf_copydata (struct mbuf*,int /*<<< orphan*/ ,int,struct ip*) ; 

__attribute__((used)) static int
gif_encapcheck(
	const struct mbuf *m,
	int off,
	int proto,
	void *arg)
{
	int error = 0;
	struct ip ip;
	struct gif_softc *sc;

	sc = (struct gif_softc *)arg;
	if (sc == NULL)
		return (error);

	GIF_LOCK(sc);
	if ((ifnet_flags(sc->gif_if) & IFF_UP) == 0)
		goto done;

	/* no physical address */
	if (!sc->gif_psrc || !sc->gif_pdst)
		goto done;

	switch (proto) {
#if INET
	case IPPROTO_IPV4:
		break;
#endif
#if INET6
	case IPPROTO_IPV6:
		break;
#endif
	default:
		goto done;
	}

	mbuf_copydata((struct mbuf *)(size_t)m, 0, sizeof (ip), &ip);

	switch (ip.ip_v) {
#if INET
	case 4:
		if (sc->gif_psrc->sa_family != AF_INET ||
		    sc->gif_pdst->sa_family != AF_INET)
			goto done;
		error = gif_encapcheck4(m, off, proto, arg);
#endif
#if INET6
	case 6:
		if (sc->gif_psrc->sa_family != AF_INET6 ||
		    sc->gif_pdst->sa_family != AF_INET6)
			goto done;
		error = gif_encapcheck6(m, off, proto, arg);
#endif
	default:
		goto done;
	}
done:
	GIF_UNLOCK(sc);
	return (error);
}
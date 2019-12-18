#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mbuf {int dummy; } ;
struct ip {int ip_v; } ;
struct gif_softc {TYPE_2__* gif_pdst; TYPE_1__* gif_psrc; int /*<<< orphan*/  gif_if; } ;
typedef  int /*<<< orphan*/  ip ;
struct TYPE_4__ {int /*<<< orphan*/  sa_family; } ;
struct TYPE_3__ {int /*<<< orphan*/  sa_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  GIF_LOCK (struct gif_softc*) ; 
 int /*<<< orphan*/  GIF_UNLOCK (struct gif_softc*) ; 
 int IFF_UP ; 
#define  IPPROTO_IPV4 129 
#define  IPPROTO_IPV6 128 
 int gif_encapcheck4 (struct mbuf const*,int,int,void*) ; 
 int gif_encapcheck6 (struct mbuf const*,int,int,void*) ; 
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
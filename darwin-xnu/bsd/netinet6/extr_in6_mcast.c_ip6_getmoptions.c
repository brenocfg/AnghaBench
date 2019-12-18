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
typedef  int /*<<< orphan*/  u_int ;
struct sockopt {int sopt_name; } ;
struct ip6_moptions {int /*<<< orphan*/  im6o_multicast_loop; int /*<<< orphan*/  im6o_multicast_hlim; TYPE_1__* im6o_multicast_ifp; } ;
struct inpcb {int /*<<< orphan*/  inp_socket; struct ip6_moptions* in6p_moptions; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_index; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int ENOPROTOOPT ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IM6O_LOCK (struct ip6_moptions*) ; 
 int /*<<< orphan*/  IM6O_UNLOCK (struct ip6_moptions*) ; 
 scalar_t__ IPPROTO_DIVERT ; 
#define  IPV6_MSFILTER 131 
#define  IPV6_MULTICAST_HOPS 130 
#define  IPV6_MULTICAST_IF 129 
#define  IPV6_MULTICAST_LOOP 128 
 scalar_t__ SOCK_DGRAM ; 
 scalar_t__ SOCK_PROTO (int /*<<< orphan*/ ) ; 
 scalar_t__ SOCK_RAW ; 
 scalar_t__ SOCK_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in6_mcast_loop ; 
 int in6p_get_source_filters (struct inpcb*,struct sockopt*) ; 
 int /*<<< orphan*/  ip6_defmcasthlim ; 
 int sooptcopyout (struct sockopt*,int /*<<< orphan*/ *,int) ; 

int
ip6_getmoptions(struct inpcb *inp, struct sockopt *sopt)
{
	struct ip6_moptions	*im6o;
	int			 error;
	u_int			 optval;

	im6o = inp->in6p_moptions;
	/*
	 * If socket is neither of type SOCK_RAW or SOCK_DGRAM,
	 * or is a divert socket, reject it.
	 */
	if (SOCK_PROTO(inp->inp_socket) == IPPROTO_DIVERT ||
	    (SOCK_TYPE(inp->inp_socket) != SOCK_RAW &&
	    SOCK_TYPE(inp->inp_socket) != SOCK_DGRAM)) {
		return (EOPNOTSUPP);
	}

	error = 0;
	switch (sopt->sopt_name) {
	case IPV6_MULTICAST_IF:
		if (im6o != NULL)
			IM6O_LOCK(im6o);
		if (im6o == NULL || im6o->im6o_multicast_ifp == NULL) {
			optval = 0;
		} else {
			optval = im6o->im6o_multicast_ifp->if_index;
		}
		if (im6o != NULL)
			IM6O_UNLOCK(im6o);
		error = sooptcopyout(sopt, &optval, sizeof(u_int));
		break;

	case IPV6_MULTICAST_HOPS:
		if (im6o == NULL) {
			optval = ip6_defmcasthlim;
		} else {
			IM6O_LOCK(im6o);
			optval = im6o->im6o_multicast_hlim;
			IM6O_UNLOCK(im6o);
		}
		error = sooptcopyout(sopt, &optval, sizeof(u_int));
		break;

	case IPV6_MULTICAST_LOOP:
		if (im6o == NULL) {
			optval = in6_mcast_loop; /* XXX VIMAGE */
		} else {
			IM6O_LOCK(im6o);
			optval = im6o->im6o_multicast_loop;
			IM6O_UNLOCK(im6o);
		}
		error = sooptcopyout(sopt, &optval, sizeof(u_int));
		break;

	case IPV6_MSFILTER:
		if (im6o == NULL) {
			error = EADDRNOTAVAIL;
		} else {
			error = in6p_get_source_filters(inp, sopt);
		}
		break;

	default:
		error = ENOPROTOOPT;
		break;
	}

	return (error);
}
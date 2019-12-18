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
struct sockopt {scalar_t__ sopt_level; int sopt_name; int sopt_valsize; } ;
struct socket {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOPROTOOPT ; 
 scalar_t__ SOL_SOCKET ; 
#define  SO_DEBUG 164 
#define  SO_DEFUNCTOK 163 
#define  SO_DELEGATED 162 
#define  SO_DELEGATED_UUID 161 
#define  SO_ERROR 160 
#define  SO_FLUSH 159 
#define  SO_ISDEFUNCT 158 
#define  SO_KEEPALIVE 157 
#define  SO_LABEL 156 
#define  SO_LINGER 155 
#define  SO_LINGER_SEC 154 
#define  SO_MARK_CELLFALLBACK 153 
#define  SO_NECP_ATTRIBUTES 152 
#define  SO_NECP_CLIENTUUID 151 
#define  SO_NKE 150 
#define  SO_NOADDRERR 149 
#define  SO_NOAPNFALLBK 148 
#define  SO_NOSIGPIPE 147 
#define  SO_NOWAKEFROMSLEEP 146 
#define  SO_NREAD 145 
#define  SO_NWRITE 144 
#define  SO_PEERLABEL 143 
#define  SO_PRIVILEGED_TRAFFIC_CLASS 142 
#define  SO_RANDOMPORT 141 
#define  SO_RCVBUF 140 
#define  SO_RCVLOWAT 139 
#define  SO_RCVTIMEO 138 
#define  SO_RECV_ANYIF 137 
#define  SO_RECV_TRAFFIC_CLASS 136 
#define  SO_RESTRICTIONS 135 
#define  SO_SNDBUF 134 
#define  SO_SNDLOWAT 133 
#define  SO_SNDTIMEO 132 
#define  SO_TRAFFIC_CLASS 131 
#define  SO_TRAFFIC_CLASS_DBG 130 
#define  SO_TYPE 129 
#define  SO_USELOOPBACK 128 
 int /*<<< orphan*/  VERIFY (int) ; 

__attribute__((used)) static int
mptcp_usr_socheckopt(struct socket *mp_so, struct sockopt *sopt)
{
#pragma unused(mp_so)
	int error = 0;

	VERIFY(sopt->sopt_level == SOL_SOCKET);

	/*
	 * We could check for sopt_dir (set/get) here, but we'll just
	 * let the caller deal with it as appropriate; therefore the
	 * following is a superset of the socket options which we
	 * allow for set/get.
	 *
	 * XXX: adi@apple.com
	 *
	 * Need to consider the following cases:
	 *
	 *   a.	Certain socket options don't have a clear definition
	 *	on the expected behavior post connect(2).  At the time
	 *	those options are issued on the MP socket, there may
	 *	be existing subflow sockets that are already connected.
	 */
	switch (sopt->sopt_name) {
	case SO_LINGER:				/* MP */
	case SO_LINGER_SEC:			/* MP */
	case SO_TYPE:				/* MP */
	case SO_NREAD:				/* MP */
	case SO_NWRITE:				/* MP */
	case SO_ERROR:				/* MP */
	case SO_SNDBUF:				/* MP */
	case SO_RCVBUF:				/* MP */
	case SO_SNDLOWAT:			/* MP */
	case SO_RCVLOWAT:			/* MP */
	case SO_SNDTIMEO:			/* MP */
	case SO_RCVTIMEO:			/* MP */
	case SO_NKE:				/* MP */
	case SO_NOSIGPIPE:			/* MP */
	case SO_NOADDRERR:			/* MP */
	case SO_LABEL:				/* MP */
	case SO_PEERLABEL:			/* MP */
	case SO_DEFUNCTOK:			/* MP */
	case SO_ISDEFUNCT:			/* MP */
	case SO_TRAFFIC_CLASS_DBG:		/* MP */
	case SO_DELEGATED:			/* MP */
	case SO_DELEGATED_UUID:			/* MP */
#if NECP
	case SO_NECP_ATTRIBUTES:
	case SO_NECP_CLIENTUUID:
#endif /* NECP */
		/*
		 * Tell the caller that these options are to be processed.
		 */
		break;

	case SO_DEBUG:				/* MP + subflow */
	case SO_KEEPALIVE:			/* MP + subflow */
	case SO_USELOOPBACK:			/* MP + subflow */
	case SO_RANDOMPORT:			/* MP + subflow */
	case SO_TRAFFIC_CLASS:			/* MP + subflow */
	case SO_RECV_TRAFFIC_CLASS:		/* MP + subflow */
	case SO_PRIVILEGED_TRAFFIC_CLASS:	/* MP + subflow */
	case SO_RECV_ANYIF:			/* MP + subflow */
	case SO_RESTRICTIONS:			/* MP + subflow */
	case SO_FLUSH:				/* MP + subflow */
	case SO_NOWAKEFROMSLEEP:
	case SO_NOAPNFALLBK:
	case SO_MARK_CELLFALLBACK:
		/*
		 * Tell the caller that these options are to be processed;
		 * these will also be recorded later by mptcp_setopt().
		 *
		 * NOTE: Only support integer option value for now.
		 */
		if (sopt->sopt_valsize != sizeof (int))
			error = EINVAL;
		break;

	default:
		/*
		 * Tell the caller to stop immediately and return an error.
		 */
		error = ENOPROTOOPT;
		break;
	}

	return (error);
}
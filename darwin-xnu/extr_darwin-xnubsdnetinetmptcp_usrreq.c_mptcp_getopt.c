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
struct sockopt {scalar_t__ sopt_level; int sopt_name; } ;
struct mptses {int mpte_svctype; int mpte_alternate_port; } ;
struct mptopt {int mpo_intval; } ;
struct TYPE_2__ {int so_flags; } ;

/* Variables and functions */
 int ENOPROTOOPT ; 
 scalar_t__ IPPROTO_TCP ; 
#define  MPTCP_ALTERNATE_PORT 140 
#define  MPTCP_SERVICE_TYPE 139 
#define  PERSIST_TIMEOUT 138 
 int SOF_NOTSENT_LOWAT ; 
#define  TCP_ADAPTIVE_READ_TIMEOUT 137 
#define  TCP_ADAPTIVE_WRITE_TIMEOUT 136 
#define  TCP_CONNECTIONTIMEOUT 135 
#define  TCP_KEEPALIVE 134 
#define  TCP_KEEPCNT 133 
#define  TCP_KEEPINTVL 132 
#define  TCP_NODELAY 131 
#define  TCP_NOTSENT_LOWAT 130 
#define  TCP_RXT_CONNDROPTIME 129 
#define  TCP_RXT_FINDROP 128 
 int mptcp_default_tcp_optval (struct mptses*,struct sockopt*,int*) ; 
 int mptcp_get_notsent_lowat (struct mptses*) ; 
 struct mptopt* mptcp_sopt_find (struct mptses*,struct sockopt*) ; 
 TYPE_1__* mptetoso (struct mptses*) ; 
 int sooptcopyout (struct sockopt*,int*,int) ; 

__attribute__((used)) static int
mptcp_getopt(struct mptses *mpte, struct sockopt *sopt)
{
	int error = 0, optval = 0;

	/*
	 * We only handle SOPT_GET for TCP level socket options; we should
	 * not get here for socket level options since they are already
	 * handled at the socket layer.
	 */
	if (sopt->sopt_level != IPPROTO_TCP) {
		error = ENOPROTOOPT;
		goto out;
	}

	switch (sopt->sopt_name) {
	case TCP_NODELAY:
	case TCP_RXT_FINDROP:
	case TCP_KEEPALIVE:
	case TCP_KEEPINTVL:
	case TCP_KEEPCNT:
	case TCP_CONNECTIONTIMEOUT:
	case TCP_RXT_CONNDROPTIME:
	case PERSIST_TIMEOUT:
	case TCP_ADAPTIVE_READ_TIMEOUT:
	case TCP_ADAPTIVE_WRITE_TIMEOUT:
	case TCP_NOTSENT_LOWAT:
	case MPTCP_SERVICE_TYPE:
	case MPTCP_ALTERNATE_PORT:
		/* eligible; get the default value just in case */
		error = mptcp_default_tcp_optval(mpte, sopt, &optval);
		break;
	default:
		/* not eligible */
		error = ENOPROTOOPT;
		break;
	}

	switch (sopt->sopt_name) {
	case TCP_NOTSENT_LOWAT:
		if (mptetoso(mpte)->so_flags & SOF_NOTSENT_LOWAT)
			optval = mptcp_get_notsent_lowat(mpte);
		else
			optval = 0;
		goto out;
	case MPTCP_SERVICE_TYPE:
		optval = mpte->mpte_svctype;
		goto out;
	case MPTCP_ALTERNATE_PORT:
		optval = mpte->mpte_alternate_port;
		goto out;
	}

	/*
	 * Search for a previously-issued TCP level socket option and
	 * return the recorded option value.  This assumes that the
	 * value did not get modified by the lower layer after it was
	 * issued at setsockopt(2) time.  If not found, we'll return
	 * the default value obtained ealier.
	 */
	if (error == 0) {
		struct mptopt *mpo;

		if ((mpo = mptcp_sopt_find(mpte, sopt)) != NULL)
			optval = mpo->mpo_intval;

		error = sooptcopyout(sopt, &optval, sizeof (int));
	}
out:
	return (error);
}
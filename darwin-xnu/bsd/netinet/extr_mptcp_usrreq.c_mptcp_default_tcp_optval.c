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
struct sockopt {scalar_t__ sopt_level; scalar_t__ sopt_dir; int sopt_name; } ;
struct mptses {int dummy; } ;

/* Variables and functions */
 int ENOPROTOOPT ; 
 scalar_t__ IPPROTO_TCP ; 
#define  MPTCP_ALTERNATE_PORT 140 
#define  MPTCP_SERVICE_TYPE 139 
#define  PERSIST_TIMEOUT 138 
 scalar_t__ SOPT_GET ; 
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
 int /*<<< orphan*/  VERIFY (int) ; 
 int mptcp_subflow_keeptime ; 
 int /*<<< orphan*/  mpte_lock_assert_held (struct mptses*) ; 
 int tcp_max_persist_timeout ; 

__attribute__((used)) static int
mptcp_default_tcp_optval(struct mptses *mpte, struct sockopt *sopt, int *optval)
{
	int error = 0;

	VERIFY(sopt->sopt_level == IPPROTO_TCP);
	VERIFY(sopt->sopt_dir == SOPT_GET);
	mpte_lock_assert_held(mpte);	/* same as MP socket lock */

	/* try to do what tcp_newtcpcb() does */
	switch (sopt->sopt_name) {
	case TCP_NODELAY:
	case TCP_RXT_FINDROP:
	case TCP_KEEPINTVL:
	case TCP_KEEPCNT:
	case TCP_CONNECTIONTIMEOUT:
	case TCP_RXT_CONNDROPTIME:
	case TCP_NOTSENT_LOWAT:
	case TCP_ADAPTIVE_READ_TIMEOUT:
	case TCP_ADAPTIVE_WRITE_TIMEOUT:
	case MPTCP_SERVICE_TYPE:
	case MPTCP_ALTERNATE_PORT:
		*optval = 0;
		break;

	case TCP_KEEPALIVE:
		*optval = mptcp_subflow_keeptime;
		break;

	case PERSIST_TIMEOUT:
		*optval = tcp_max_persist_timeout;
		break;

	default:
		error = ENOPROTOOPT;
		break;
	}
	return (error);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int uint32_t ;
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  tcp_ci ;
struct socket {int so_state; int /*<<< orphan*/  so_error; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int sin_len; TYPE_2__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct inpcb {int inp_flags; TYPE_3__ inp_faddr; int /*<<< orphan*/  inp_fport; TYPE_1__ inp_laddr; int /*<<< orphan*/  inp_lport; struct ifnet* inp_last_outifp; } ;
struct ifnet {int if_index; } ;
struct conninfo_tcp {int sin_len; TYPE_2__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sin ;
typedef  int sae_connid_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int CIAUX_TCP ; 
 int CIF_BOUND_IF ; 
 int CIF_BOUND_IP ; 
 int CIF_BOUND_PORT ; 
 int CIF_CONNECTED ; 
 int CIF_PREFERRED ; 
 int EINVAL ; 
 int INP_ANONPORT ; 
 int INP_BOUND_IF ; 
 int INP_INADDR_ANY ; 
 scalar_t__ IPPROTO_TCP ; 
 int SAE_CONNID_ALL ; 
 int SAE_CONNID_ANY ; 
 scalar_t__ SOCK_PROTO (struct socket*) ; 
 int SS_ISCONNECTED ; 
 int /*<<< orphan*/  USER_ADDR_NULL ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in*,int) ; 
 int copyout (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 
 int /*<<< orphan*/  tcp_getconninfo (struct socket*,struct sockaddr_in*) ; 

int
in_getconninfo(struct socket *so, sae_connid_t cid, uint32_t *flags,
    uint32_t *ifindex, int32_t *soerror, user_addr_t src, socklen_t *src_len,
    user_addr_t dst, socklen_t *dst_len, uint32_t *aux_type,
    user_addr_t aux_data, uint32_t *aux_len)
{
	struct inpcb *inp = sotoinpcb(so);
	struct sockaddr_in sin;
	struct ifnet *ifp = NULL;
	int error = 0;
	u_int32_t copy_len = 0;

	/*
	 * Don't test for INPCB_STATE_DEAD since this may be called
	 * after SOF_PCBCLEARING is set, e.g. after tcp_close().
	 */
	if (inp == NULL) {
		error = EINVAL;
		goto out;
	}

	if (cid != SAE_CONNID_ANY && cid != SAE_CONNID_ALL && cid != 1) {
		error = EINVAL;
		goto out;
	}

	ifp = inp->inp_last_outifp;
	*ifindex = ((ifp != NULL) ? ifp->if_index : 0);
	*soerror = so->so_error;
	*flags = 0;
	if (so->so_state & SS_ISCONNECTED)
		*flags |= (CIF_CONNECTED | CIF_PREFERRED);
	if (inp->inp_flags & INP_BOUND_IF)
		*flags |= CIF_BOUND_IF;
	if (!(inp->inp_flags & INP_INADDR_ANY))
		*flags |= CIF_BOUND_IP;
	if (!(inp->inp_flags & INP_ANONPORT))
		*flags |= CIF_BOUND_PORT;

	bzero(&sin, sizeof (sin));
	sin.sin_len = sizeof (sin);
	sin.sin_family = AF_INET;

	/* source address and port */
	sin.sin_port = inp->inp_lport;
	sin.sin_addr.s_addr = inp->inp_laddr.s_addr;
	if (*src_len == 0) {
		*src_len = sin.sin_len;
	} else {
		if (src != USER_ADDR_NULL) {
			copy_len = min(*src_len, sizeof (sin));
			error = copyout(&sin, src, copy_len);
			if (error != 0)
				goto out;
			*src_len = copy_len;
		}
	}

	/* destination address and port */
	sin.sin_port = inp->inp_fport;
	sin.sin_addr.s_addr = inp->inp_faddr.s_addr;
	if (*dst_len == 0) {
		*dst_len = sin.sin_len;
	} else {
		if (dst != USER_ADDR_NULL) {
			copy_len = min(*dst_len, sizeof (sin));
			error = copyout(&sin, dst, copy_len);
			if (error != 0)
				goto out;
			*dst_len = copy_len;
		}
	}

	if (SOCK_PROTO(so) == IPPROTO_TCP) {
		struct conninfo_tcp tcp_ci;

		*aux_type = CIAUX_TCP;
		if (*aux_len == 0) {
			*aux_len = sizeof (tcp_ci);
		} else {
			if (aux_data != USER_ADDR_NULL) {
				copy_len = min(*aux_len, sizeof (tcp_ci));
				bzero(&tcp_ci, sizeof (tcp_ci));
				tcp_getconninfo(so, &tcp_ci);
				error = copyout(&tcp_ci, aux_data, copy_len);
				if (error != 0)
					goto out;
				*aux_len = copy_len;
			}
		}
	} else {
		*aux_type = 0;
		*aux_len = 0;
	}

out:
	return (error);
}
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
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int uint32_t ;
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  tcp_ci ;
struct socket {int so_state; int /*<<< orphan*/  so_error; } ;
struct sockaddr_in6 {int sin6_len; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_family; } ;
struct in6pcb {int in6p_flags; int /*<<< orphan*/  in6p_faddr; int /*<<< orphan*/  in6p_fport; int /*<<< orphan*/  in6p_laddr; int /*<<< orphan*/  in6p_lport; struct ifnet* in6p_last_outifp; } ;
struct ifnet {int if_index; } ;
struct conninfo_tcp {int sin6_len; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_family; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sin6 ;
typedef  int sae_connid_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int CIAUX_TCP ; 
 int CIF_BOUND_IF ; 
 int CIF_BOUND_IP ; 
 int CIF_BOUND_PORT ; 
 int CIF_CONNECTED ; 
 int CIF_PREFERRED ; 
 int EINVAL ; 
 int INP_ANONPORT ; 
 int INP_BOUND_IF ; 
 int INP_IN6ADDR_ANY ; 
 scalar_t__ IPPROTO_TCP ; 
 int SAE_CONNID_ALL ; 
 int SAE_CONNID_ANY ; 
 scalar_t__ SOCK_PROTO (struct socket*) ; 
 int SS_ISCONNECTED ; 
 int /*<<< orphan*/  USER_ADDR_NULL ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in6*,int) ; 
 int copyout (struct sockaddr_in6*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  in6_recoverscope (struct sockaddr_in6*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int min (int,int) ; 
 struct in6pcb* sotoin6pcb (struct socket*) ; 
 int /*<<< orphan*/  tcp_getconninfo (struct socket*,struct sockaddr_in6*) ; 

int
in6_getconninfo(struct socket *so, sae_connid_t cid, uint32_t *flags,
    uint32_t *ifindex, int32_t *soerror, user_addr_t src, socklen_t *src_len,
    user_addr_t dst, socklen_t *dst_len, uint32_t *aux_type,
    user_addr_t aux_data, uint32_t *aux_len)
{
	struct in6pcb *in6p = sotoin6pcb(so);
	struct sockaddr_in6 sin6;
	struct ifnet *ifp = NULL;
	int error = 0;
	u_int32_t copy_len = 0;

	/*
	 * Don't test for INPCB_STATE_DEAD since this may be called
	 * after SOF_PCBCLEARING is set, e.g. after tcp_close().
	 */
	if (in6p == NULL) {
		error = EINVAL;
		goto out;
	}

	if (cid != SAE_CONNID_ANY && cid != SAE_CONNID_ALL && cid != 1) {
		error = EINVAL;
		goto out;
	}

	ifp = in6p->in6p_last_outifp;
	*ifindex = ((ifp != NULL) ? ifp->if_index : 0);
	*soerror = so->so_error;
	*flags = 0;
	if (so->so_state & SS_ISCONNECTED)
		*flags |= (CIF_CONNECTED | CIF_PREFERRED);
	if (in6p->in6p_flags & INP_BOUND_IF)
		*flags |= CIF_BOUND_IF;
	if (!(in6p->in6p_flags & INP_IN6ADDR_ANY))
		*flags |= CIF_BOUND_IP;
	if (!(in6p->in6p_flags & INP_ANONPORT))
		*flags |= CIF_BOUND_PORT;

	bzero(&sin6, sizeof (sin6));
	sin6.sin6_len = sizeof (sin6);
	sin6.sin6_family = AF_INET6;

	/* source address and port */
	sin6.sin6_port = in6p->in6p_lport;
	in6_recoverscope(&sin6, &in6p->in6p_laddr, NULL);
	if (*src_len == 0) {
		*src_len = sin6.sin6_len;
	} else {
		if (src != USER_ADDR_NULL) {
			copy_len = min(*src_len, sizeof (sin6));
			error = copyout(&sin6, src, copy_len);
			if (error != 0)
				goto out;
			*src_len = copy_len;
		}
	}

	/* destination address and port */
	sin6.sin6_port = in6p->in6p_fport;
	in6_recoverscope(&sin6, &in6p->in6p_faddr, NULL);
	if (*dst_len == 0) {
		*dst_len = sin6.sin6_len;
	} else {
		if (dst != USER_ADDR_NULL) {
			copy_len = min(*dst_len, sizeof (sin6));
			error = copyout(&sin6, dst, copy_len);
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
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
struct unpcb {int unp_flags; TYPE_1__* unp_conn; int /*<<< orphan*/  unp_peercred; } ;
struct sockopt {int sopt_dir; int const sopt_name; } ;
struct socket {int so_flags; int /*<<< orphan*/  last_uuid; int /*<<< orphan*/  e_uuid; int /*<<< orphan*/  last_pid; int /*<<< orphan*/  e_pid; int /*<<< orphan*/  so_type; } ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  peerpid ;
struct TYPE_2__ {struct socket* unp_socket; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTCONN ; 
 int EOPNOTSUPP ; 
#define  LOCAL_PEERCRED 134 
#define  LOCAL_PEEREPID 133 
#define  LOCAL_PEEREUUID 132 
#define  LOCAL_PEERPID 131 
#define  LOCAL_PEERUUID 130 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int SOF_DELEGATED ; 
#define  SOPT_GET 129 
#define  SOPT_SET 128 
 int UNP_HAVEPC ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int) ; 
 int sooptcopyout (struct sockopt*,int /*<<< orphan*/ *,int) ; 
 struct unpcb* sotounpcb (struct socket*) ; 
 int /*<<< orphan*/  unp_get_locks_in_order (struct socket*,struct socket*) ; 

int
uipc_ctloutput(struct socket *so, struct sockopt *sopt)
{
	struct unpcb *unp = sotounpcb(so);
	int error = 0;
	pid_t peerpid;
	struct socket *peerso;

	switch (sopt->sopt_dir) {
	case SOPT_GET:
		switch (sopt->sopt_name) {
		case LOCAL_PEERCRED:
			if (unp->unp_flags & UNP_HAVEPC) {
				error = sooptcopyout(sopt, &unp->unp_peercred,
				    sizeof (unp->unp_peercred));
			} else {
				if (so->so_type == SOCK_STREAM)
					error = ENOTCONN;
				else
					error = EINVAL;
			}
			break;
		case LOCAL_PEERPID:
		case LOCAL_PEEREPID:
			if (unp->unp_conn == NULL) {
				error = ENOTCONN;
				break;
			}
			peerso = unp->unp_conn->unp_socket;
			if (peerso == NULL)
				panic("peer is connected but has no socket?");
			unp_get_locks_in_order(so, peerso);
			if (sopt->sopt_name == LOCAL_PEEREPID &&
			    peerso->so_flags & SOF_DELEGATED)
				peerpid = peerso->e_pid;
			else
				peerpid = peerso->last_pid;
			socket_unlock(peerso, 1);
			error = sooptcopyout(sopt, &peerpid, sizeof (peerpid));
			break;
		case LOCAL_PEERUUID:
		case LOCAL_PEEREUUID:
			if (unp->unp_conn == NULL) {
				error = ENOTCONN;
				break;
			}
			peerso = unp->unp_conn->unp_socket;
			if (peerso == NULL)
				panic("peer is connected but has no socket?");
			unp_get_locks_in_order(so, peerso);
			if (sopt->sopt_name == LOCAL_PEEREUUID &&
			    peerso->so_flags & SOF_DELEGATED)
				error = sooptcopyout(sopt, &peerso->e_uuid,
				    sizeof (peerso->e_uuid));
			else
				error = sooptcopyout(sopt, &peerso->last_uuid,
				    sizeof (peerso->last_uuid));
			socket_unlock(peerso, 1);
			break;
		default:
			error = EOPNOTSUPP;
			break;
		}
		break;
	case SOPT_SET:
	default:
		error = EOPNOTSUPP;
		break;
	}

	return (error);
}
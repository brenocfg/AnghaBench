#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_7__ {struct socket* sb_so; } ;
struct TYPE_6__ {struct socket* sb_so; int /*<<< orphan*/  sb_flags; } ;
struct socket {int so_type; scalar_t__ so_usecount; int /*<<< orphan*/  so_flags; int /*<<< orphan*/  so_background_thread; int /*<<< orphan*/  so_options; int /*<<< orphan*/  so_evlist; int /*<<< orphan*/  so_state; scalar_t__ next_unlock_lr; scalar_t__ next_lock_lr; TYPE_2__ so_snd; TYPE_1__ so_rcv; struct protosw* so_proto; int /*<<< orphan*/  so_cred; int /*<<< orphan*/  e_uuid; void* e_pid; void* e_upid; int /*<<< orphan*/  so_vuuid; int /*<<< orphan*/  last_uuid; void* last_pid; void* last_upid; int /*<<< orphan*/  so_comp; int /*<<< orphan*/  so_incomp; } ;
struct protosw {int pr_type; TYPE_4__* pr_domain; TYPE_3__* pr_usrreqs; } ;
struct proc {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  nas_socket_domain_other_total; int /*<<< orphan*/  nas_socket_domain_multipath_total; int /*<<< orphan*/  nas_socket_domain_system_total; int /*<<< orphan*/  nas_socket_inet6_dgram_total; int /*<<< orphan*/  nas_socket_inet6_stream_total; int /*<<< orphan*/  nas_socket_domain_inet6_total; int /*<<< orphan*/  nas_socket_domain_key_total; int /*<<< orphan*/  nas_socket_domain_ndrv_total; int /*<<< orphan*/  nas_socket_domain_route_total; int /*<<< orphan*/  nas_socket_inet_dgram_total; int /*<<< orphan*/  nas_socket_inet_stream_total; int /*<<< orphan*/  nas_socket_domain_inet_total; int /*<<< orphan*/  nas_socket_domain_local_total; } ;
struct TYPE_9__ {int /*<<< orphan*/  dom_refs; } ;
struct TYPE_8__ {int (* pru_attach ) (struct socket*,int,struct proc*) ;} ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int ENOBUFS ; 
 int EPROTONOSUPPORT ; 
 int EPROTOTYPE ; 
 int /*<<< orphan*/  INC_ATOMIC_INT64_LIM (int /*<<< orphan*/ ) ; 
#define  PF_INET 135 
#define  PF_INET6 134 
#define  PF_KEY 133 
#define  PF_LOCAL 132 
#define  PF_MULTIPATH 131 
#define  PF_NDRV 130 
#define  PF_ROUTE 129 
#define  PF_SYSTEM 128 
 struct proc* PROC_NULL ; 
 int /*<<< orphan*/  SB_RECV ; 
 int SOCF_ASYNC ; 
 int SOCK_STREAM ; 
 int /*<<< orphan*/  SOF_DELEGATED ; 
 int /*<<< orphan*/  SOF_NODEFUNCT ; 
 int /*<<< orphan*/  SO_DEBUG ; 
 int /*<<< orphan*/  SS_NBIO ; 
 int /*<<< orphan*/  SS_NOFDREF ; 
 int /*<<< orphan*/  SS_PRIV ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TASK_POLICY_NEW_SOCKETS_BG ; 
 int /*<<< orphan*/  TRAFFIC_MGT_SO_BACKGROUND ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  atomic_add_32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 int /*<<< orphan*/  kauth_cred_proc_ref (struct proc*) ; 
 int /*<<< orphan*/  mac_socket_label_associate (int /*<<< orphan*/ ,struct socket*) ; 
 TYPE_5__ net_api_stats ; 
 int /*<<< orphan*/ * pffinddomain (int) ; 
 struct protosw* pffindproto (int,int,int) ; 
 int /*<<< orphan*/ * pffindprotonotype (int,int) ; 
 struct protosw* pffindtype (int,int) ; 
 scalar_t__ proc_get_effective_thread_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_getexecutableuuid (struct proc*,int /*<<< orphan*/ ,int) ; 
 void* proc_pid (struct proc*) ; 
 int /*<<< orphan*/  proc_pidoriginatoruuid (int /*<<< orphan*/ ,int) ; 
 void* proc_uniqueid (struct proc*) ; 
 int /*<<< orphan*/  sflt_initsock (struct socket*) ; 
 int /*<<< orphan*/  so_set_default_traffic_class (struct socket*) ; 
 struct socket* soalloc (int,int,int) ; 
 int /*<<< orphan*/  socket_set_traffic_mgt_flags (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sofreelastref (struct socket*,int) ; 
 int stub1 (struct socket*,int,struct proc*) ; 
 int /*<<< orphan*/  suser (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
socreate_internal(int dom, struct socket **aso, int type, int proto,
    struct proc *p, uint32_t flags, struct proc *ep)
{
	struct protosw *prp;
	struct socket *so;
	int error = 0;

#if TCPDEBUG
	extern int tcpconsdebug;
#endif

	VERIFY(aso != NULL);
	*aso = NULL;

	if (proto != 0)
		prp = pffindproto(dom, proto, type);
	else
		prp = pffindtype(dom, type);

	if (prp == NULL || prp->pr_usrreqs->pru_attach == NULL) {
		if (pffinddomain(dom) == NULL)
			return (EAFNOSUPPORT);
		if (proto != 0) {
			if (pffindprotonotype(dom, proto) != NULL)
				return (EPROTOTYPE);
		}
		return (EPROTONOSUPPORT);
	}
	if (prp->pr_type != type)
		return (EPROTOTYPE);
	so = soalloc(1, dom, type);
	if (so == NULL)
		return (ENOBUFS);

	switch (dom) {
		case PF_LOCAL:
			INC_ATOMIC_INT64_LIM(net_api_stats.nas_socket_domain_local_total);
			break;
		case PF_INET:
			INC_ATOMIC_INT64_LIM(net_api_stats.nas_socket_domain_inet_total);
			if (type == SOCK_STREAM) {
				INC_ATOMIC_INT64_LIM(net_api_stats.nas_socket_inet_stream_total);
			} else  {
				INC_ATOMIC_INT64_LIM(net_api_stats.nas_socket_inet_dgram_total);
			}
			break;
		case PF_ROUTE:
			INC_ATOMIC_INT64_LIM(net_api_stats.nas_socket_domain_route_total);
			break;
		case PF_NDRV:
			INC_ATOMIC_INT64_LIM(net_api_stats.nas_socket_domain_ndrv_total);
			break;
		case PF_KEY:
			INC_ATOMIC_INT64_LIM(net_api_stats.nas_socket_domain_key_total);
			break;
		case PF_INET6:
			INC_ATOMIC_INT64_LIM(net_api_stats.nas_socket_domain_inet6_total);
			if (type == SOCK_STREAM) {
				INC_ATOMIC_INT64_LIM(net_api_stats.nas_socket_inet6_stream_total);
			} else {
				INC_ATOMIC_INT64_LIM(net_api_stats.nas_socket_inet6_dgram_total);
			}
			break;
		case PF_SYSTEM:
			INC_ATOMIC_INT64_LIM(net_api_stats.nas_socket_domain_system_total);
			break;
		case PF_MULTIPATH:
			INC_ATOMIC_INT64_LIM(net_api_stats.nas_socket_domain_multipath_total);
			break;
		default:
			INC_ATOMIC_INT64_LIM(net_api_stats.nas_socket_domain_other_total);
			break;
	}

	if (flags & SOCF_ASYNC)
		so->so_state |= SS_NBIO;

	TAILQ_INIT(&so->so_incomp);
	TAILQ_INIT(&so->so_comp);
	so->so_type = type;
	so->last_upid = proc_uniqueid(p);
	so->last_pid = proc_pid(p);
	proc_getexecutableuuid(p, so->last_uuid, sizeof (so->last_uuid));
	proc_pidoriginatoruuid(so->so_vuuid, sizeof(so->so_vuuid));

	if (ep != PROC_NULL && ep != p) {
		so->e_upid = proc_uniqueid(ep);
		so->e_pid = proc_pid(ep);
		proc_getexecutableuuid(ep, so->e_uuid, sizeof (so->e_uuid));
		so->so_flags |= SOF_DELEGATED;
	}

	so->so_cred = kauth_cred_proc_ref(p);
	if (!suser(kauth_cred_get(), NULL))
		so->so_state |= SS_PRIV;

	so->so_proto = prp;
	so->so_rcv.sb_flags |= SB_RECV;
	so->so_rcv.sb_so = so->so_snd.sb_so = so;
	so->next_lock_lr = 0;
	so->next_unlock_lr = 0;

#if CONFIG_MACF_SOCKET
	mac_socket_label_associate(kauth_cred_get(), so);
#endif /* MAC_SOCKET */

	/*
	 * Attachment will create the per pcb lock if necessary and
	 * increase refcount for creation, make sure it's done before
	 * socket is inserted in lists.
	 */
	so->so_usecount++;

	error = (*prp->pr_usrreqs->pru_attach)(so, proto, p);
	if (error != 0) {
		/*
		 * Warning:
		 * If so_pcb is not zero, the socket will be leaked,
		 * so protocol attachment handler must be coded carefuly
		 */
		so->so_state |= SS_NOFDREF;
		VERIFY(so->so_usecount > 0);
		so->so_usecount--;
		sofreelastref(so, 1);	/* will deallocate the socket */
		return (error);
	}

	atomic_add_32(&prp->pr_domain->dom_refs, 1);
	TAILQ_INIT(&so->so_evlist);

	/* Attach socket filters for this protocol */
	sflt_initsock(so);
#if TCPDEBUG
	if (tcpconsdebug == 2)
		so->so_options |= SO_DEBUG;
#endif
	so_set_default_traffic_class(so);

	/*
	 * If this thread or task is marked to create backgrounded sockets,
	 * mark the socket as background.
	 */
	if (proc_get_effective_thread_policy(current_thread(),
	    TASK_POLICY_NEW_SOCKETS_BG)) {
		socket_set_traffic_mgt_flags(so, TRAFFIC_MGT_SO_BACKGROUND);
		so->so_background_thread = current_thread();
	}

	switch (dom) {
	/*
	 * Don't mark Unix domain, system or multipath sockets as
	 * eligible for defunct by default.
	 */
	case PF_LOCAL:
	case PF_SYSTEM:
	case PF_MULTIPATH:
		so->so_flags |= SOF_NODEFUNCT;
		break;
	default:
		break;
	}

	/*
	 * Entitlements can't be checked at socket creation time except if the
	 * application requested a feature guarded by a privilege (c.f., socket
	 * delegation).
	 * The priv(9) and the Sandboxing APIs are designed with the idea that
	 * a privilege check should only be triggered by a userland request.
	 * A privilege check at socket creation time is time consuming and
	 * could trigger many authorisation error messages from the security
	 * APIs.
	 */

	*aso = so;

	return (0);
}
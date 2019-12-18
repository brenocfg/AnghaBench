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
struct TYPE_9__ {int sb_flags; int /*<<< orphan*/  sb_hiwat; struct socket* sb_so; } ;
struct TYPE_10__ {int sb_flags; int /*<<< orphan*/  sb_hiwat; struct socket* sb_so; } ;
struct socket {int so_qlen; int so_incqlen; int so_qlimit; int so_options; int so_state; int so_flags; int so_usecount; int so_flags1; int /*<<< orphan*/  so_timeo; int /*<<< orphan*/  so_incomp; int /*<<< orphan*/  so_comp; struct socket* so_head; TYPE_3__* so_proto; TYPE_4__ so_snd; TYPE_5__ so_rcv; int /*<<< orphan*/  so_traffic_class; int /*<<< orphan*/  so_background_thread; int /*<<< orphan*/  so_evlist; scalar_t__ next_unlock_lr; scalar_t__ next_lock_lr; int /*<<< orphan*/  e_uuid; int /*<<< orphan*/  e_upid; int /*<<< orphan*/  e_pid; int /*<<< orphan*/  last_uuid; int /*<<< orphan*/  last_upid; int /*<<< orphan*/  last_pid; int /*<<< orphan*/  so_cred; int /*<<< orphan*/  so_pgid; int /*<<< orphan*/  so_linger; int /*<<< orphan*/  so_type; } ;
typedef  int /*<<< orphan*/  lck_mtx_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_8__ {TYPE_2__* pr_domain; scalar_t__ pr_unlock; TYPE_1__* pr_usrreqs; int /*<<< orphan*/ * (* pr_getlock ) (struct socket*,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  dom_refs; int /*<<< orphan*/ * dom_mtx; } ;
struct TYPE_6__ {scalar_t__ (* pru_attach ) (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int SB_RECV ; 
 int SB_USRSIZE ; 
 int /*<<< orphan*/  SOCK_DOM (struct socket*) ; 
 int SOF1_TRAFFIC_MGT_SO_BACKGROUND ; 
 int SOF_BINDRANDOMPORT ; 
 int SOF_DELEGATED ; 
 int SOF_INCOMP_INPROGRESS ; 
 int SOF_NOADDRAVAIL ; 
 int SOF_NODEFUNCT ; 
 int SOF_NOSIGPIPE ; 
 int SOF_NOTIFYCONFLICT ; 
 int SOF_NOTSENT_LOWAT ; 
 int SOF_NPX_SETOPTSHUT ; 
 int SOF_PRIVILEGED_TRAFFIC_CLASS ; 
 int SOF_REUSESHAREUID ; 
 int SOF_USELRO ; 
 int SO_ACCEPTCONN ; 
 int SS_COMP ; 
 int SS_INCOMP ; 
 int SS_NOFDREF ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_add_32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kauth_cred_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_socket_label_associate_accept (struct socket*,struct socket*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sflt_initsock (struct socket*) ; 
 int /*<<< orphan*/  so_acquire_accept_list (struct socket*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  so_list ; 
 int /*<<< orphan*/  so_release_accept_list (struct socket*) ; 
 struct socket* soalloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soclose (struct socket*) ; 
 int /*<<< orphan*/  sodealloc (struct socket*) ; 
 int somaxconn ; 
 int /*<<< orphan*/  soqlencomp ; 
 scalar_t__ soqlimitcompat ; 
 scalar_t__ soreserve (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sorwakeup (struct socket*) ; 
 int /*<<< orphan*/ * stub1 (struct socket*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct socket *
sonewconn_internal(struct socket *head, int connstatus)
{
	int so_qlen, error = 0;
	struct socket *so;
	lck_mtx_t *mutex_held;

	if (head->so_proto->pr_getlock != NULL)
		mutex_held = (*head->so_proto->pr_getlock)(head, 0);
	else
		mutex_held = head->so_proto->pr_domain->dom_mtx;
	LCK_MTX_ASSERT(mutex_held, LCK_MTX_ASSERT_OWNED);

	if (!soqlencomp) {
		/*
		 * This is the default case; so_qlen represents the
		 * sum of both incomplete and completed queues.
		 */
		so_qlen = head->so_qlen;
	} else {
		/*
		 * When kern.ipc.soqlencomp is set to 1, so_qlen
		 * represents only the completed queue.  Since we
		 * cannot let the incomplete queue goes unbounded
		 * (in case of SYN flood), we cap the incomplete
		 * queue length to at most somaxconn, and use that
		 * as so_qlen so that we fail immediately below.
		 */
		so_qlen = head->so_qlen - head->so_incqlen;
		if (head->so_incqlen > somaxconn)
			so_qlen = somaxconn;
	}

	if (so_qlen >=
	    (soqlimitcompat ? head->so_qlimit : (3 * head->so_qlimit / 2)))
		return ((struct socket *)0);
	so = soalloc(1, SOCK_DOM(head), head->so_type);
	if (so == NULL)
		return ((struct socket *)0);
	/* check if head was closed during the soalloc */
	if (head->so_proto == NULL) {
		sodealloc(so);
		return ((struct socket *)0);
	}

	so->so_type = head->so_type;
	so->so_options = head->so_options &~ SO_ACCEPTCONN;
	so->so_linger = head->so_linger;
	so->so_state = head->so_state | SS_NOFDREF;
	so->so_proto = head->so_proto;
	so->so_timeo = head->so_timeo;
	so->so_pgid  = head->so_pgid;
	kauth_cred_ref(head->so_cred);
	so->so_cred = head->so_cred;
	so->last_pid = head->last_pid;
	so->last_upid = head->last_upid;
	memcpy(so->last_uuid, head->last_uuid, sizeof (so->last_uuid));
	if (head->so_flags & SOF_DELEGATED) {
		so->e_pid = head->e_pid;
		so->e_upid = head->e_upid;
		memcpy(so->e_uuid, head->e_uuid, sizeof (so->e_uuid));
	}
	/* inherit socket options stored in so_flags */
	so->so_flags = head->so_flags &
	    (SOF_NOSIGPIPE | SOF_NOADDRAVAIL | SOF_REUSESHAREUID |
	    SOF_NOTIFYCONFLICT | SOF_BINDRANDOMPORT | SOF_NPX_SETOPTSHUT |
	    SOF_NODEFUNCT | SOF_PRIVILEGED_TRAFFIC_CLASS| SOF_NOTSENT_LOWAT |
	    SOF_USELRO | SOF_DELEGATED);
	so->so_usecount = 1;
	so->next_lock_lr = 0;
	so->next_unlock_lr = 0;

	so->so_rcv.sb_flags |= SB_RECV;	/* XXX */
	so->so_rcv.sb_so = so->so_snd.sb_so = so;
	TAILQ_INIT(&so->so_evlist);

#if CONFIG_MACF_SOCKET
	mac_socket_label_associate_accept(head, so);
#endif

	/* inherit traffic management properties of listener */
	so->so_flags1 |=
	    head->so_flags1 & (SOF1_TRAFFIC_MGT_SO_BACKGROUND);
	so->so_background_thread = head->so_background_thread;
	so->so_traffic_class = head->so_traffic_class;

	if (soreserve(so, head->so_snd.sb_hiwat, head->so_rcv.sb_hiwat)) {
		sodealloc(so);
		return ((struct socket *)0);
	}
	so->so_rcv.sb_flags |= (head->so_rcv.sb_flags & SB_USRSIZE);
	so->so_snd.sb_flags |= (head->so_snd.sb_flags & SB_USRSIZE);

	/*
	 * Must be done with head unlocked to avoid deadlock
	 * for protocol with per socket mutexes.
	 */
	if (head->so_proto->pr_unlock)
		socket_unlock(head, 0);
	if (((*so->so_proto->pr_usrreqs->pru_attach)(so, 0, NULL) != 0) ||
	    error) {
		sodealloc(so);
		if (head->so_proto->pr_unlock)
			socket_lock(head, 0);
		return ((struct socket *)0);
	}
	if (head->so_proto->pr_unlock) {
		socket_lock(head, 0);
		/*
		 * Radar 7385998 Recheck that the head is still accepting
		 * to avoid race condition when head is getting closed.
		 */
		if ((head->so_options & SO_ACCEPTCONN) == 0) {
			so->so_state &= ~SS_NOFDREF;
			soclose(so);
			return ((struct socket *)0);
		}
	}

	atomic_add_32(&so->so_proto->pr_domain->dom_refs, 1);

	/* Insert in head appropriate lists */
	so_acquire_accept_list(head, NULL);

	so->so_head = head;

	/*
	 * Since this socket is going to be inserted into the incomp
	 * queue, it can be picked up by another thread in
	 * tcp_dropdropablreq to get dropped before it is setup..
	 * To prevent this race, set in-progress flag which can be
	 * cleared later
	 */
	so->so_flags |= SOF_INCOMP_INPROGRESS;

	if (connstatus) {
		TAILQ_INSERT_TAIL(&head->so_comp, so, so_list);
		so->so_state |= SS_COMP;
	} else {
		TAILQ_INSERT_TAIL(&head->so_incomp, so, so_list);
		so->so_state |= SS_INCOMP;
		head->so_incqlen++;
	}
	head->so_qlen++;

	so_release_accept_list(head);

	/* Attach socket filters for this protocol */
	sflt_initsock(so);

	if (connstatus) {
		so->so_state |= connstatus;
		sorwakeup(head);
		wakeup((caddr_t)&head->so_timeo);
	}
	return (so);
}
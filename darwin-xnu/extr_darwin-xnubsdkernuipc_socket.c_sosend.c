#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ user_ssize_t ;
typedef  scalar_t__ uint16_t ;
struct uio {int dummy; } ;
struct TYPE_17__ {scalar_t__ sb_lowat; int sb_hiwat; int /*<<< orphan*/  sb_cc; } ;
struct socket {int so_state; scalar_t__ so_type; int so_flags; int so_options; scalar_t__ so_pktheadroom; int so_flags1; TYPE_8__ so_snd; struct mbuf* so_temp; TYPE_7__* so_proto; struct mbuf* so_tail; } ;
struct sockaddr {int dummy; } ;
struct proc {TYPE_3__* p_stats; } ;
struct TYPE_14__ {scalar_t__ len; } ;
struct TYPE_13__ {int ext_size; } ;
struct mbuf {int m_len; int m_flags; struct mbuf* m_next; TYPE_5__ m_pkthdr; TYPE_4__ m_ext; int /*<<< orphan*/  m_data; } ;
struct inpcb {TYPE_1__* inp_last_outifp; } ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int boolean_t ;
struct TYPE_16__ {int pr_flags; TYPE_6__* pr_usrreqs; } ;
struct TYPE_15__ {int (* pru_send ) (struct socket*,int,struct mbuf*,struct sockaddr*,struct mbuf*,struct proc*) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  ru_msgsnd; } ;
struct TYPE_12__ {TYPE_2__ p_ru; } ;
struct TYPE_10__ {int if_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int DBG_FNC_SOSEND ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int EINVAL ; 
 int EJUSTRETURN ; 
 int ENOBUFS ; 
 scalar_t__ ENTR_SHOULDTRACE ; 
 int EOPNOTSUPP ; 
 int EWOULDBLOCK ; 
 int FALSE ; 
 int IFF_LOOPBACK ; 
 scalar_t__ INT_MAX ; 
 int /*<<< orphan*/  KERNEL_DEBUG (int,struct socket*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  KERNEL_ENERGYTRACE (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int M16KCLBYTES ; 
 int MBIGCLBYTES ; 
 int MCLBYTES ; 
 int /*<<< orphan*/  MGET (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGETHDR (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MHLEN ; 
 int /*<<< orphan*/  MH_ALIGN (struct mbuf*,int) ; 
 scalar_t__ MINCLSIZE ; 
 int MLEN ; 
 int MSG_DONTROUTE ; 
 int MSG_EOF ; 
 int MSG_EOR ; 
 int MSG_FLUSH ; 
 int MSG_HOLD ; 
 int MSG_OOB ; 
 int MSG_SEND ; 
 int MSG_SKIPCFIL ; 
 int /*<<< orphan*/  MT_DATA ; 
 int M_EOR ; 
 int M_EXT ; 
 int M_LEADINGSPACE (struct mbuf*) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int M_PKTHDR ; 
 int /*<<< orphan*/  M_WAIT ; 
 int /*<<< orphan*/  OSIncrementAtomicLong (int /*<<< orphan*/ *) ; 
 int PRUS_EOF ; 
 int PRUS_MORETOCOME ; 
 int PRUS_OOB ; 
 int PR_ATOMIC ; 
 int PR_IMPLOPCL ; 
 int ROUNDUP (int,int) ; 
 scalar_t__ SOCK_CHECK_DOM (struct socket*,int /*<<< orphan*/ ) ; 
 scalar_t__ SOCK_STREAM ; 
 int SOF1_IF_2KCL ; 
 int SOF_ENABLE_MSGS ; 
 int SOF_MULTIPAGES ; 
 int SO_DONTROUTE ; 
 int SS_NBIO ; 
 int TRUE ; 
 int /*<<< orphan*/  VM_KERNEL_ADDRPERM (struct socket*) ; 
 int _MHLEN ; 
 int _MLEN ; 
 int /*<<< orphan*/  caddr_t ; 
 struct proc* current_proc () ; 
 void* imin (int,int) ; 
 int /*<<< orphan*/  kEnTrActKernSockWrite ; 
 int /*<<< orphan*/  kEnTrFlagNoWork ; 
 int /*<<< orphan*/  kEnTrFlagNonBlocking ; 
 struct mbuf* m_dup (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  m_freem_list (struct mbuf*) ; 
 struct mbuf* m_getpackets_internal (unsigned int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int min (scalar_t__,scalar_t__) ; 
 scalar_t__ msgq_sbspace (struct socket*,struct mbuf*) ; 
 int /*<<< orphan*/  mtod (struct mbuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ njcl ; 
 scalar_t__ sbspace (TYPE_8__*) ; 
 int /*<<< orphan*/  sbunlock (TYPE_8__*,int) ; 
 int sflt_data_out (struct socket*,struct sockaddr*,struct mbuf**,struct mbuf**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  so_update_last_owner_locked (struct socket*,struct proc*) ; 
 int /*<<< orphan*/  so_update_policy (struct socket*) ; 
 int /*<<< orphan*/  sock_data_filt_flag_oob ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int) ; 
 int /*<<< orphan*/  soclearfastopen (struct socket*) ; 
 scalar_t__ soreserveheadroom ; 
 scalar_t__ sosendallatonce (struct socket*) ; 
 scalar_t__ sosendbigcl_ignore_capab ; 
 int sosendcheck (struct socket*,struct sockaddr*,scalar_t__,int,int,int,int*,struct mbuf*) ; 
 scalar_t__ sosendjcl ; 
 scalar_t__ sosendjcl_ignore_capab ; 
 int sosendmaxchain ; 
 scalar_t__ sosendminchain ; 
 struct inpcb* sotoinpcb (struct socket*) ; 
 int stub1 (struct socket*,int,struct mbuf*,struct sockaddr*,struct mbuf*,struct proc*) ; 
 scalar_t__ uio_resid (struct uio*) ; 
 int uiomove (int /*<<< orphan*/ ,scalar_t__,struct uio*) ; 

int
sosend(struct socket *so, struct sockaddr *addr, struct uio *uio,
    struct mbuf *top, struct mbuf *control, int flags)
{
	struct mbuf **mp;
	struct mbuf *m, *freelist = NULL;
	user_ssize_t space, len, resid, orig_resid;
	int clen = 0, error, dontroute, mlen, sendflags;
	int atomic = sosendallatonce(so) || top;
	int sblocked = 0;
	struct proc *p = current_proc();
	struct mbuf *control_copy = NULL;
	uint16_t headroom = 0;
	boolean_t en_tracing = FALSE;

	if (uio != NULL)
		resid = uio_resid(uio);
	else
		resid = top->m_pkthdr.len;

	KERNEL_DEBUG((DBG_FNC_SOSEND | DBG_FUNC_START), so, resid,
	    so->so_snd.sb_cc, so->so_snd.sb_lowat, so->so_snd.sb_hiwat);

	socket_lock(so, 1);

	/*
	 * trace if tracing & network (vs. unix) sockets & and
	 * non-loopback
	 */
	if (ENTR_SHOULDTRACE &&
	    (SOCK_CHECK_DOM(so, AF_INET) || SOCK_CHECK_DOM(so, AF_INET6))) {
		struct inpcb *inp = sotoinpcb(so);
		if (inp->inp_last_outifp != NULL &&
		    !(inp->inp_last_outifp->if_flags & IFF_LOOPBACK)) {
			en_tracing = TRUE;
			KERNEL_ENERGYTRACE(kEnTrActKernSockWrite, DBG_FUNC_START,
			    VM_KERNEL_ADDRPERM(so),
			    ((so->so_state & SS_NBIO) ? kEnTrFlagNonBlocking : 0),
			    (int64_t)resid);
			orig_resid = resid;
		}
	}

	/*
	 * Re-injection should not affect process accounting
	 */
	if ((flags & MSG_SKIPCFIL) == 0) {
		so_update_last_owner_locked(so, p);
		so_update_policy(so);

#if NECP
		so_update_necp_policy(so, NULL, addr);
#endif /* NECP */
	}

	if (so->so_type != SOCK_STREAM && (flags & MSG_OOB) != 0) {
		error = EOPNOTSUPP;
		goto out_locked;
	}

	/*
	 * In theory resid should be unsigned.
	 * However, space must be signed, as it might be less than 0
	 * if we over-committed, and we must use a signed comparison
	 * of space and resid.  On the other hand, a negative resid
	 * causes us to loop sending 0-length segments to the protocol.
	 *
	 * Usually, MSG_EOR isn't used on SOCK_STREAM type sockets.
	 * But it will be used by sockets doing message delivery.
	 *
	 * Note: We limit resid to be a positive int value as we use
	 * imin() to set bytes_to_copy -- radr://14558484
	 */
	if (resid < 0 || resid > INT_MAX || (so->so_type == SOCK_STREAM &&
	    !(so->so_flags & SOF_ENABLE_MSGS) && (flags & MSG_EOR))) {
		error = EINVAL;
		goto out_locked;
	}

	dontroute = (flags & MSG_DONTROUTE) &&
	    (so->so_options & SO_DONTROUTE) == 0 &&
	    (so->so_proto->pr_flags & PR_ATOMIC);
	OSIncrementAtomicLong(&p->p_stats->p_ru.ru_msgsnd);

	if (control != NULL)
		clen = control->m_len;

	if (soreserveheadroom != 0)
		headroom = so->so_pktheadroom;

	do {
		error = sosendcheck(so, addr, resid, clen, atomic, flags,
		    &sblocked, control);
		if (error)
			goto out_locked;

		mp = &top;
		if (so->so_flags & SOF_ENABLE_MSGS)
			space = msgq_sbspace(so, control);
		else
			space = sbspace(&so->so_snd) - clen;
		space += ((flags & MSG_OOB) ? 1024 : 0);

		do {
			if (uio == NULL) {
				/*
				 * Data is prepackaged in "top".
				 */
				resid = 0;
				if (flags & MSG_EOR)
					top->m_flags |= M_EOR;
			} else {
				int chainlength;
				int bytes_to_copy;
				boolean_t jumbocl;
				boolean_t bigcl;
				int bytes_to_alloc;

				bytes_to_copy = imin(resid, space);

				bytes_to_alloc = bytes_to_copy;
				if (top == NULL)
					bytes_to_alloc += headroom;

				if (sosendminchain > 0)
					chainlength = 0;
				else
					chainlength = sosendmaxchain;

				/*
				 * Use big 4 KB cluster when the outgoing interface
				 * does not prefer 2 KB clusters
				 */
				bigcl = !(so->so_flags1 & SOF1_IF_2KCL) ||
				    sosendbigcl_ignore_capab;

				/*
				 * Attempt to use larger than system page-size
				 * clusters for large writes only if there is
				 * a jumbo cluster pool and if the socket is
				 * marked accordingly.
				 */
				jumbocl = sosendjcl && njcl > 0 &&
				    ((so->so_flags & SOF_MULTIPAGES) ||
				    sosendjcl_ignore_capab) &&
				    bigcl;

				socket_unlock(so, 0);

				do {
					int num_needed;
					int hdrs_needed = (top == NULL) ? 1 : 0;

					/*
					 * try to maintain a local cache of mbuf
					 * clusters needed to complete this
					 * write the list is further limited to
					 * the number that are currently needed
					 * to fill the socket this mechanism
					 * allows a large number of mbufs/
					 * clusters to be grabbed under a single
					 * mbuf lock... if we can't get any
					 * clusters, than fall back to trying
					 * for mbufs if we fail early (or
					 * miscalcluate the number needed) make
					 * sure to release any clusters we
					 * haven't yet consumed.
					 */
					if (freelist == NULL &&
					    bytes_to_alloc > MBIGCLBYTES &&
					    jumbocl) {
						num_needed =
						    bytes_to_alloc / M16KCLBYTES;

						if ((bytes_to_alloc -
						    (num_needed * M16KCLBYTES))
						    >= MINCLSIZE)
							num_needed++;

						freelist =
						    m_getpackets_internal(
						    (unsigned int *)&num_needed,
						    hdrs_needed, M_WAIT, 0,
						    M16KCLBYTES);
						/*
						 * Fall back to 4K cluster size
						 * if allocation failed
						 */
					}

					if (freelist == NULL &&
					    bytes_to_alloc > MCLBYTES &&
					    bigcl) {
						num_needed =
						    bytes_to_alloc / MBIGCLBYTES;

						if ((bytes_to_alloc -
						    (num_needed * MBIGCLBYTES)) >=
						    MINCLSIZE)
							num_needed++;

						freelist =
						    m_getpackets_internal(
						    (unsigned int *)&num_needed,
						    hdrs_needed, M_WAIT, 0,
						    MBIGCLBYTES);
						/*
						 * Fall back to cluster size
						 * if allocation failed
						 */
					}

					/*
					 * Allocate a cluster as we want to
					 * avoid to split the data in more
					 * that one segment and using MINCLSIZE
					 * would lead us to allocate two mbufs
					 */
					if (soreserveheadroom != 0 &&
					    freelist == NULL &&
					    ((top == NULL &&
					    bytes_to_alloc > _MHLEN) ||
					    bytes_to_alloc > _MLEN)) {
						num_needed = ROUNDUP(bytes_to_alloc, MCLBYTES) /
						    MCLBYTES;
						freelist =
						    m_getpackets_internal(
						    (unsigned int *)&num_needed,
						    hdrs_needed, M_WAIT, 0,
						    MCLBYTES);
						/*
						 * Fall back to a single mbuf
						 * if allocation failed
						 */
					} else if (freelist == NULL &&
					    bytes_to_alloc > MINCLSIZE) {
						num_needed =
						    bytes_to_alloc / MCLBYTES;

						if ((bytes_to_alloc -
						    (num_needed * MCLBYTES)) >=
						    MINCLSIZE)
							num_needed++;

						freelist =
						    m_getpackets_internal(
						    (unsigned int *)&num_needed,
						    hdrs_needed, M_WAIT, 0,
						    MCLBYTES);
						/*
						 * Fall back to a single mbuf
						 * if allocation failed
						 */
					}
					/*
					 * For datagram protocols, leave
					 * headroom for protocol headers
					 * in the first cluster of the chain
					 */
					if (freelist != NULL && atomic &&
					    top == NULL && headroom > 0) {
						freelist->m_data += headroom;
					}

					/*
					 * Fall back to regular mbufs without
					 * reserving the socket headroom
					 */
					if (freelist == NULL) {
						if (top == NULL)
							MGETHDR(freelist,
							    M_WAIT, MT_DATA);
						else
							MGET(freelist,
							    M_WAIT, MT_DATA);

						if (freelist == NULL) {
							error = ENOBUFS;
							socket_lock(so, 0);
							goto out_locked;
						}
						/*
						 * For datagram protocols,
						 * leave room for protocol
						 * headers in first mbuf.
						 */
						if (atomic && top == NULL &&
						    bytes_to_copy < MHLEN) {
							MH_ALIGN(freelist,
							    bytes_to_copy);
						}
					}
					m = freelist;
					freelist = m->m_next;
					m->m_next = NULL;

					if ((m->m_flags & M_EXT))
						mlen = m->m_ext.ext_size -
						    M_LEADINGSPACE(m);
					else if ((m->m_flags & M_PKTHDR))
						mlen =
						    MHLEN - M_LEADINGSPACE(m);
					else
						mlen = MLEN - M_LEADINGSPACE(m);
					len = imin(mlen, bytes_to_copy);

					chainlength += len;

					space -= len;

					error = uiomove(mtod(m, caddr_t),
					    len, uio);

					resid = uio_resid(uio);

					m->m_len = len;
					*mp = m;
					top->m_pkthdr.len += len;
					if (error)
						break;
					mp = &m->m_next;
					if (resid <= 0) {
						if (flags & MSG_EOR)
							top->m_flags |= M_EOR;
						break;
					}
					bytes_to_copy = min(resid, space);

				} while (space > 0 &&
				    (chainlength < sosendmaxchain || atomic ||
				    resid < MINCLSIZE));

				socket_lock(so, 0);

				if (error)
					goto out_locked;
			}

			if (flags & (MSG_HOLD|MSG_SEND)) {
				/* Enqueue for later, go away if HOLD */
				struct mbuf *mb1;
				if (so->so_temp && (flags & MSG_FLUSH)) {
					m_freem(so->so_temp);
					so->so_temp = NULL;
				}
				if (so->so_temp)
					so->so_tail->m_next = top;
				else
					so->so_temp = top;
				mb1 = top;
				while (mb1->m_next)
					mb1 = mb1->m_next;
				so->so_tail = mb1;
				if (flags & MSG_HOLD) {
					top = NULL;
					goto out_locked;
				}
				top = so->so_temp;
			}
			if (dontroute)
				so->so_options |= SO_DONTROUTE;

			/*
			 * Compute flags here, for pru_send and NKEs
			 *
			 * If the user set MSG_EOF, the protocol
			 * understands this flag and nothing left to
			 * send then use PRU_SEND_EOF instead of PRU_SEND.
			 */
			sendflags = (flags & MSG_OOB) ? PRUS_OOB :
			    ((flags & MSG_EOF) &&
			    (so->so_proto->pr_flags & PR_IMPLOPCL) &&
			    (resid <= 0)) ? PRUS_EOF :
			    /* If there is more to send set PRUS_MORETOCOME */
			    (resid > 0 && space > 0) ? PRUS_MORETOCOME : 0;

			if ((flags & MSG_SKIPCFIL) == 0) {
				/*
				 * Socket filter processing
				 */
				error = sflt_data_out(so, addr, &top,
				    &control, (sendflags & MSG_OOB) ?
				    sock_data_filt_flag_oob : 0);
				if (error) {
					if (error == EJUSTRETURN) {
						error = 0;
						clen = 0;
						control = NULL;
						top = NULL;
					}
					goto out_locked;
				}
#if CONTENT_FILTER
				/*
				 * Content filter processing
				 */
				error = cfil_sock_data_out(so, addr, top,
				    control, sendflags);
				if (error) {
					if (error == EJUSTRETURN) {
						error = 0;
						clen = 0;
						control = NULL;
						top = NULL;
						}
					goto out_locked;
				}
#endif /* CONTENT_FILTER */
			}
			if (so->so_flags & SOF_ENABLE_MSGS) {
				/*
				 * Make a copy of control mbuf,
				 * so that msg priority can be
				 * passed to subsequent mbufs.
				 */
				control_copy = m_dup(control, M_NOWAIT);
			}
			error = (*so->so_proto->pr_usrreqs->pru_send)
			    (so, sendflags, top, addr, control, p);

			if (flags & MSG_SEND)
				so->so_temp = NULL;

			if (dontroute)
				so->so_options &= ~SO_DONTROUTE;

			clen = 0;
			control = control_copy;
			control_copy = NULL;
			top = NULL;
			mp = &top;
			if (error)
				goto out_locked;
		} while (resid && space > 0);
	} while (resid);

out_locked:
	if (sblocked)
		sbunlock(&so->so_snd, FALSE);	/* will unlock socket */
	else
		socket_unlock(so, 1);
	if (top != NULL)
		m_freem(top);
	if (control != NULL)
		m_freem(control);
	if (freelist != NULL)
		m_freem_list(freelist);
	if (control_copy != NULL)
		m_freem(control_copy);

	soclearfastopen(so);

	if (en_tracing) {
		/* resid passed here is the bytes left in uio */
		KERNEL_ENERGYTRACE(kEnTrActKernSockWrite, DBG_FUNC_END,
		    VM_KERNEL_ADDRPERM(so),
		    ((error == EWOULDBLOCK) ? kEnTrFlagNoWork : 0),
		    (int64_t)(orig_resid - resid));
	}
	KERNEL_DEBUG(DBG_FNC_SOSEND | DBG_FUNC_END, so, resid,
	    so->so_snd.sb_cc, space, error);

	return (error);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int u_int64_t ;
struct timeval {int tv_sec; int tv_usec; } ;
struct timespec {int tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_10__ {int /*<<< orphan*/  ro_dst; } ;
struct route {int /*<<< orphan*/  ro_dst; } ;
struct sockaddr_in6 {int dn_dir; int dn_client; int /*<<< orphan*/  dn_ipoa; int /*<<< orphan*/  dn_flags; int /*<<< orphan*/  dn_exthdrs; int /*<<< orphan*/  dn_unfragpartlen; int /*<<< orphan*/  dn_alwaysfrag; int /*<<< orphan*/  dn_mtu; int /*<<< orphan*/  dn_origifp; int /*<<< orphan*/  dn_dst6; TYPE_2__ dn_ro6; int /*<<< orphan*/  dn_ro6_pmtu; int /*<<< orphan*/  dn_dst; struct route dn_ro; int /*<<< orphan*/  dn_ifp; int /*<<< orphan*/  dn_pf_rule; TYPE_4__* dn_ipfw_rule; } ;
struct sockaddr_in {int dn_dir; int dn_client; int /*<<< orphan*/  dn_ipoa; int /*<<< orphan*/  dn_flags; int /*<<< orphan*/  dn_exthdrs; int /*<<< orphan*/  dn_unfragpartlen; int /*<<< orphan*/  dn_alwaysfrag; int /*<<< orphan*/  dn_mtu; int /*<<< orphan*/  dn_origifp; int /*<<< orphan*/  dn_dst6; TYPE_2__ dn_ro6; int /*<<< orphan*/  dn_ro6_pmtu; int /*<<< orphan*/  dn_dst; struct route dn_ro; int /*<<< orphan*/  dn_ifp; int /*<<< orphan*/  dn_pf_rule; TYPE_4__* dn_ipfw_rule; } ;
struct TYPE_11__ {int len; } ;
struct mbuf {struct mbuf* m_nextpkt; TYPE_3__ m_pkthdr; } ;
struct m_tag {int dummy; } ;
struct ip_fw_args {scalar_t__ fwa_flags; int /*<<< orphan*/ * fwa_ipoa; int /*<<< orphan*/  fwa_oflags; struct sockaddr_in6* fwa_exthdrs; int /*<<< orphan*/  fwa_unfragpartlen; int /*<<< orphan*/  fwa_alwaysfrag; int /*<<< orphan*/  fwa_mtu; int /*<<< orphan*/  fwa_origifp; struct sockaddr_in6* fwa_dst6; TYPE_1__* fwa_ro6; scalar_t__ fwa_ro6_pmtu; struct sockaddr_in6* fwa_dst; struct route* fwa_ro; int /*<<< orphan*/  fwa_oif; int /*<<< orphan*/  fwa_pf_rule; TYPE_4__* fwa_ipfw_rule; int /*<<< orphan*/  fwa_id; } ;
struct ip6_exthdrs {int dummy; } ;
struct dn_pkt_tag {int dn_dir; int dn_client; int /*<<< orphan*/  dn_ipoa; int /*<<< orphan*/  dn_flags; int /*<<< orphan*/  dn_exthdrs; int /*<<< orphan*/  dn_unfragpartlen; int /*<<< orphan*/  dn_alwaysfrag; int /*<<< orphan*/  dn_mtu; int /*<<< orphan*/  dn_origifp; int /*<<< orphan*/  dn_dst6; TYPE_2__ dn_ro6; int /*<<< orphan*/  dn_ro6_pmtu; int /*<<< orphan*/  dn_dst; struct route dn_ro; int /*<<< orphan*/  dn_ifp; int /*<<< orphan*/  dn_pf_rule; TYPE_4__* dn_ipfw_rule; } ;
struct TYPE_14__ {scalar_t__ elements; } ;
struct dn_flow_set {int parent_nr; int fs_nr; scalar_t__ plr; int flags_fs; scalar_t__ qsize; int /*<<< orphan*/  backlogged; scalar_t__ weight; struct dn_pipe* pipe; } ;
struct dn_pipe {scalar_t__ V; scalar_t__ numbytes; void* sched_time; int /*<<< orphan*/  pipe_nr; TYPE_6__ scheduler_heap; TYPE_6__ not_eligible_heap; int /*<<< orphan*/  idle_heap; int /*<<< orphan*/  sum; scalar_t__ bandwidth; struct dn_flow_set fs; } ;
struct dn_flow_queue {int tot_bytes; scalar_t__ len_bytes; scalar_t__ len; scalar_t__ S; scalar_t__ F; int /*<<< orphan*/  drops; void* sched_time; struct mbuf* head; struct mbuf* tail; int /*<<< orphan*/  tot_pkts; } ;
struct TYPE_13__ {scalar_t__ opcode; } ;
typedef  TYPE_5__ ipfw_insn ;
typedef  scalar_t__ dn_key ;
struct TYPE_12__ {int act_ofs; int fw_flg; TYPE_5__* cmd; } ;
struct TYPE_9__ {int /*<<< orphan*/  ro_dst; } ;

/* Variables and functions */
 int DN_CLIENT_IPFW ; 
 int DN_CLIENT_PF ; 
 scalar_t__ DN_IS_PIPE ; 
 int DN_IS_RED ; 
 scalar_t__ DN_KEY_GT (scalar_t__,scalar_t__) ; 
 int DN_NOERROR ; 
 int DN_QSIZE_IS_BYTES ; 
 int DN_TO_IP6_OUT ; 
 int DN_TO_IP_OUT ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  F_LEN (TYPE_5__*) ; 
 int IP_FW_F_COMMAND ; 
 int IP_FW_F_PIPE ; 
 int /*<<< orphan*/  KERNEL_MODULE_TAG_ID ; 
 int /*<<< orphan*/  KERNEL_TAG_TYPE_DUMMYNET ; 
 void* MAX64 (scalar_t__,scalar_t__) ; 
 int MY_M ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 scalar_t__ O_LOG ; 
 scalar_t__ O_PIPE ; 
 scalar_t__ SET_TICKS (struct mbuf*,struct dn_flow_queue*,struct dn_pipe*) ; 
 scalar_t__ VM_KERNEL_ADDRPERM (struct mbuf*) ; 
 int /*<<< orphan*/  bcopy (struct sockaddr_in6*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bsd_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct timespec*) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in6*,int) ; 
 void* curr_time ; 
 int /*<<< orphan*/  dn_mutex ; 
 int /*<<< orphan*/  dummynet ; 
 int /*<<< orphan*/  dummynet_send (struct mbuf*) ; 
 struct dn_flow_queue* find_queue (struct dn_flow_set*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_extract (int /*<<< orphan*/ *,struct dn_flow_queue*) ; 
 int /*<<< orphan*/  heap_insert (TYPE_6__*,scalar_t__,struct dn_flow_queue*) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 struct dn_flow_set* locate_flowset (int) ; 
 struct dn_pipe* locate_pipe (int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct m_tag* m_tag_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  m_tag_prepend (struct mbuf*,struct m_tag*) ; 
 int /*<<< orphan*/  microuptime (struct timeval*) ; 
 scalar_t__ my_random () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  ready_event (struct dn_flow_queue*,struct mbuf**,struct mbuf**) ; 
 int /*<<< orphan*/  ready_event_wfq (struct dn_pipe*,struct mbuf**,struct mbuf**) ; 
 TYPE_6__ ready_heap ; 
 scalar_t__ red_drops (struct dn_flow_set*,struct dn_flow_queue*,int) ; 
 int /*<<< orphan*/  route_copyout (struct route*,struct route*,int) ; 
 int timer_enabled ; 

__attribute__((used)) static int
dummynet_io(struct mbuf *m, int pipe_nr, int dir, struct ip_fw_args *fwa, int client)
{
    struct mbuf *head = NULL, *tail = NULL;
    struct dn_pkt_tag *pkt;
    struct m_tag *mtag;
    struct dn_flow_set *fs = NULL;
    struct dn_pipe *pipe ;
    u_int64_t len = m->m_pkthdr.len ;
    struct dn_flow_queue *q = NULL ;
    int is_pipe = 0;
    struct timespec ts;
    struct timeval	tv;

    DPRINTF(("dummynet_io m: 0x%llx pipe: %d dir: %d client: %d\n",
        (uint64_t)VM_KERNEL_ADDRPERM(m), pipe_nr, dir, client));

#if IPFIREWALL
#if IPFW2
    if (client == DN_CLIENT_IPFW) {
        ipfw_insn *cmd = fwa->fwa_ipfw_rule->cmd + fwa->fwa_ipfw_rule->act_ofs;

        if (cmd->opcode == O_LOG)
	    cmd += F_LEN(cmd);
        is_pipe = (cmd->opcode == O_PIPE);
    }
#else
    if (client == DN_CLIENT_IPFW)
        is_pipe = (fwa->fwa_ipfw_rule->fw_flg & IP_FW_F_COMMAND) == IP_FW_F_PIPE;
#endif
#endif /* IPFIREWALL */

#if DUMMYNET
    if (client == DN_CLIENT_PF)
    	is_pipe = fwa->fwa_flags == DN_IS_PIPE ? 1 : 0;
#endif /* DUMMYNET */

    pipe_nr &= 0xffff ;

 	lck_mtx_lock(dn_mutex);

	/* make all time measurements in milliseconds (ms) -
         * here we convert secs and usecs to msecs (just divide the
         * usecs and take the closest whole number).
	 */
    microuptime(&tv);
	curr_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);

   /*
     * This is a dummynet rule, so we expect an O_PIPE or O_QUEUE rule.
     */
    if (is_pipe) {
		pipe = locate_pipe(pipe_nr);
		if (pipe != NULL)
			fs = &(pipe->fs);
	} else
		fs = locate_flowset(pipe_nr);


    if (fs == NULL){
	goto dropit ;	/* this queue/pipe does not exist! */
    }
    pipe = fs->pipe ;
    if (pipe == NULL) { /* must be a queue, try find a matching pipe */
	pipe = locate_pipe(fs->parent_nr);

	if (pipe != NULL)
	    fs->pipe = pipe ;
	else {
	    printf("dummynet: no pipe %d for queue %d, drop pkt\n",
		fs->parent_nr, fs->fs_nr);
	    goto dropit ;
	}
    }
    q = find_queue(fs, &(fwa->fwa_id));
    if ( q == NULL )
	goto dropit ;		/* cannot allocate queue		*/
    /*
     * update statistics, then check reasons to drop pkt
     */
    q->tot_bytes += len ;
    q->tot_pkts++ ;
    if ( fs->plr && (my_random() < fs->plr))
	goto dropit ;		/* random pkt drop			*/
    if ( fs->flags_fs & DN_QSIZE_IS_BYTES) {
    	if (q->len_bytes > fs->qsize)
	    goto dropit ;	/* queue size overflow			*/
    } else {
	if (q->len >= fs->qsize)
	    goto dropit ;	/* queue count overflow			*/
    }
    if ( fs->flags_fs & DN_IS_RED && red_drops(fs, q, len) )
	goto dropit ;

    /* XXX expensive to zero, see if we can remove it*/
    mtag = m_tag_create(KERNEL_MODULE_TAG_ID, KERNEL_TAG_TYPE_DUMMYNET,
    		sizeof(struct dn_pkt_tag), M_NOWAIT, m);
    if ( mtag == NULL )
		goto dropit ;		/* cannot allocate packet header	*/
    m_tag_prepend(m, mtag);	/* attach to mbuf chain */

    pkt = (struct dn_pkt_tag *)(mtag+1);
    bzero(pkt, sizeof(struct dn_pkt_tag));
    /* ok, i can handle the pkt now... */
    /* build and enqueue packet + parameters */
    /*
     * PF is checked before ipfw so remember ipfw rule only when
     * the caller is ipfw. When the caller is PF, fwa_ipfw_rule
     * is a fake rule just used for convenience
     */
    if (client == DN_CLIENT_IPFW)
    	pkt->dn_ipfw_rule = fwa->fwa_ipfw_rule;
    pkt->dn_pf_rule = fwa->fwa_pf_rule;
    pkt->dn_dir = dir ;
    pkt->dn_client = client;

    pkt->dn_ifp = fwa->fwa_oif;
    if (dir == DN_TO_IP_OUT) {
		/*
		 * We need to copy *ro because for ICMP pkts (and maybe others)
		 * the caller passed a pointer into the stack; dst might also be
		 * a pointer into *ro so it needs to be updated.
		 */
		if (fwa->fwa_ro) {
			route_copyout(&pkt->dn_ro, fwa->fwa_ro, sizeof (pkt->dn_ro));
		}
		if (fwa->fwa_dst) {
			if (fwa->fwa_dst == (struct sockaddr_in *)&fwa->fwa_ro->ro_dst) /* dst points into ro */
				fwa->fwa_dst = (struct sockaddr_in *)&(pkt->dn_ro.ro_dst) ;

			bcopy (fwa->fwa_dst, &pkt->dn_dst, sizeof(pkt->dn_dst));
		}
    } else if (dir == DN_TO_IP6_OUT) {
		if (fwa->fwa_ro6) {
			route_copyout((struct route *)&pkt->dn_ro6,
			    (struct route *)fwa->fwa_ro6, sizeof (pkt->dn_ro6));
		}
		if (fwa->fwa_ro6_pmtu) {
			route_copyout((struct route *)&pkt->dn_ro6_pmtu,
			    (struct route *)fwa->fwa_ro6_pmtu, sizeof (pkt->dn_ro6_pmtu));
		}
		if (fwa->fwa_dst6) {
			if (fwa->fwa_dst6 == (struct sockaddr_in6 *)&fwa->fwa_ro6->ro_dst) /* dst points into ro */
				fwa->fwa_dst6 = (struct sockaddr_in6 *)&(pkt->dn_ro6.ro_dst) ;

			bcopy (fwa->fwa_dst6, &pkt->dn_dst6, sizeof(pkt->dn_dst6));
		}
		pkt->dn_origifp = fwa->fwa_origifp;
		pkt->dn_mtu = fwa->fwa_mtu;
		pkt->dn_alwaysfrag = fwa->fwa_alwaysfrag;
		pkt->dn_unfragpartlen = fwa->fwa_unfragpartlen;
		if (fwa->fwa_exthdrs) {
			bcopy (fwa->fwa_exthdrs, &pkt->dn_exthdrs, sizeof(pkt->dn_exthdrs));
			/*
			 * Need to zero out the source structure so the mbufs
			 * won't be freed by ip6_output()
			 */
			bzero(fwa->fwa_exthdrs, sizeof(struct ip6_exthdrs));
		}
    }
    if (dir == DN_TO_IP_OUT || dir == DN_TO_IP6_OUT) {
		pkt->dn_flags = fwa->fwa_oflags;
		if (fwa->fwa_ipoa != NULL)
			pkt->dn_ipoa = *(fwa->fwa_ipoa);
    }
    if (q->head == NULL)
	q->head = m;
    else
	q->tail->m_nextpkt = m;
    q->tail = m;
    q->len++;
    q->len_bytes += len ;

    if ( q->head != m )		/* flow was not idle, we are done */
	goto done;
    /*
     * If we reach this point the flow was previously idle, so we need
     * to schedule it. This involves different actions for fixed-rate or
     * WF2Q queues.
     */
    if (is_pipe) {
	/*
	 * Fixed-rate queue: just insert into the ready_heap.
	 */
	dn_key t = 0 ;
	if (pipe->bandwidth)
	    t = SET_TICKS(m, q, pipe);
	q->sched_time = curr_time ;
	if (t == 0)	/* must process it now */
	    ready_event( q , &head, &tail );
	else
	    heap_insert(&ready_heap, curr_time + t , q );
    } else {
	/*
	 * WF2Q. First, compute start time S: if the flow was idle (S=F+1)
	 * set S to the virtual time V for the controlling pipe, and update
	 * the sum of weights for the pipe; otherwise, remove flow from
	 * idle_heap and set S to max(F,V).
	 * Second, compute finish time F = S + len/weight.
	 * Third, if pipe was idle, update V=max(S, V).
	 * Fourth, count one more backlogged flow.
	 */
	if (DN_KEY_GT(q->S, q->F)) { /* means timestamps are invalid */
	    q->S = pipe->V ;
	    pipe->sum += fs->weight ; /* add weight of new queue */
	} else {
	    heap_extract(&(pipe->idle_heap), q);
	    q->S = MAX64(q->F, pipe->V ) ;
	}
	q->F = q->S + ( len<<MY_M )/(u_int64_t) fs->weight;

	if (pipe->not_eligible_heap.elements == 0 &&
		pipe->scheduler_heap.elements == 0)
	    pipe->V = MAX64 ( q->S, pipe->V );
	fs->backlogged++ ;
	/*
	 * Look at eligibility. A flow is not eligibile if S>V (when
	 * this happens, it means that there is some other flow already
	 * scheduled for the same pipe, so the scheduler_heap cannot be
	 * empty). If the flow is not eligible we just store it in the
	 * not_eligible_heap. Otherwise, we store in the scheduler_heap
	 * and possibly invoke ready_event_wfq() right now if there is
	 * leftover credit.
	 * Note that for all flows in scheduler_heap (SCH), S_i <= V,
	 * and for all flows in not_eligible_heap (NEH), S_i > V .
	 * So when we need to compute max( V, min(S_i) ) forall i in SCH+NEH,
	 * we only need to look into NEH.
	 */
	if (DN_KEY_GT(q->S, pipe->V) ) { /* not eligible */
	    if (pipe->scheduler_heap.elements == 0)
		printf("dummynet: ++ ouch! not eligible but empty scheduler!\n");
	    heap_insert(&(pipe->not_eligible_heap), q->S, q);
	} else {
	    heap_insert(&(pipe->scheduler_heap), q->F, q);
	    if (pipe->numbytes >= 0) { /* pipe is idle */
		if (pipe->scheduler_heap.elements != 1)
		    printf("dummynet: OUCH! pipe should have been idle!\n");
		DPRINTF(("dummynet: waking up pipe %d at %d\n",
			pipe->pipe_nr, (int)(q->F >> MY_M)));
		pipe->sched_time = curr_time ;
		ready_event_wfq(pipe, &head, &tail);
	    }
	}
    }
done:
	/* start the timer and set global if not already set */
	if (!timer_enabled) {
		ts.tv_sec = 0;
		ts.tv_nsec = 1 * 1000000;	// 1ms
		timer_enabled = 1;
		bsd_timeout(dummynet, NULL, &ts);
	}

	lck_mtx_unlock(dn_mutex);

	if (head != NULL) {
		dummynet_send(head);
	}

    return 0;

dropit:
    if (q)
	q->drops++ ;
	lck_mtx_unlock(dn_mutex);
    m_freem(m);
    return ( (fs && (fs->flags_fs & DN_NOERROR)) ? 0 : ENOBUFS);
}
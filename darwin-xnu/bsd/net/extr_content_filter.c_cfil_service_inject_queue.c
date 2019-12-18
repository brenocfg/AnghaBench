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
typedef  int uint64_t ;
struct socket {int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_rcv; int /*<<< orphan*/  m_flags; } ;
struct cfil_queue {int dummy; } ;
struct cfi_buf {unsigned int cfi_pending_first; int cfi_pending_mbcnt; int cfi_pending_mbnum; struct cfil_queue cfi_inject_q; } ;
struct cfil_info {int cfi_flags; struct cfi_buf cfi_rcv; struct cfi_buf cfi_snd; } ;
typedef  struct socket* mbuf_t ;
typedef  int errno_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  cfs_inject_q_in_fail; int /*<<< orphan*/  cfs_inject_q_out_fail; int /*<<< orphan*/  cfs_inject_q_nomem; int /*<<< orphan*/  cfs_inject_q_nobufs; int /*<<< orphan*/  cfs_inject_q_in_passed; int /*<<< orphan*/  cfs_inject_q_out_passed; } ;

/* Variables and functions */
 int CFIF_CLOSE_WAIT ; 
 int CFIF_RETRY_INJECT_IN ; 
 int CFIF_RETRY_INJECT_OUT ; 
 int CFIF_SHUT_WR ; 
 int /*<<< orphan*/  CFIL_INFO_VERIFY (struct cfil_info*) ; 
 int /*<<< orphan*/  CFIL_LOG (int /*<<< orphan*/ ,char*,...) ; 
 int ENOBUFS ; 
 int ENOMEM ; 
 int IS_UDP (struct socket*) ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  M_SKIPCFIL ; 
 int /*<<< orphan*/  OSAddAtomic64 (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSIncrementAtomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHUT_WR ; 
 int TRUE ; 
 scalar_t__ VM_KERNEL_ADDRPERM (struct socket*) ; 
 unsigned int cfil_data_length (struct socket*,int*,int*) ; 
 scalar_t__ cfil_filters_attached (struct socket*) ; 
 int /*<<< orphan*/  cfil_info_buf_verify (struct cfi_buf*) ; 
 int /*<<< orphan*/  cfil_info_log (int /*<<< orphan*/ ,struct cfil_info*,char*) ; 
 scalar_t__ cfil_queue_empty (struct cfil_queue*) ; 
 struct socket* cfil_queue_first (struct cfil_queue*) ; 
 int /*<<< orphan*/  cfil_queue_len (struct cfil_queue*) ; 
 int /*<<< orphan*/  cfil_queue_remove (struct cfil_queue*,struct socket*,unsigned int) ; 
 scalar_t__ cfil_sock_data_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfil_sock_notify_shutdown (struct socket*,int /*<<< orphan*/ ) ; 
 TYPE_1__ cfil_stats ; 
 scalar_t__ remote_addr_ptr ; 
 scalar_t__ sbappendchain (int /*<<< orphan*/ *,struct socket*,int /*<<< orphan*/ ) ; 
 scalar_t__ sbappendstream (int /*<<< orphan*/ *,struct socket*) ; 
 int /*<<< orphan*/  socket_lock_assert_owned (struct socket*) ; 
 int /*<<< orphan*/  sorwakeup (struct socket*) ; 
 int sosend_reinject (struct socket*,int /*<<< orphan*/ *,struct socket*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soshutdownlock_final (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sowwakeup (struct socket*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cfil_service_inject_queue(struct socket *so, struct cfil_info *cfil_info, int outgoing)
{
	mbuf_t data;
	unsigned int datalen;
	int mbcnt = 0;
	int mbnum = 0;
	errno_t error = 0;
	struct cfi_buf *cfi_buf;
	struct cfil_queue *inject_q;
	int need_rwakeup = 0;
	int count = 0;

	if (cfil_info == NULL)
		return (0);

	socket_lock_assert_owned(so);

	if (outgoing) {
		cfi_buf = &cfil_info->cfi_snd;
		cfil_info->cfi_flags &= ~CFIF_RETRY_INJECT_OUT;
	} else {
		cfi_buf = &cfil_info->cfi_rcv;
		cfil_info->cfi_flags &= ~CFIF_RETRY_INJECT_IN;
	}
	inject_q = &cfi_buf->cfi_inject_q;

	if (cfil_queue_empty(inject_q))
		return (0);

#if DATA_DEBUG | VERDICT_DEBUG
	CFIL_LOG(LOG_ERR, "CFIL: SERVICE INJECT-Q: <so %llx> outgoing %d queue len %llu",
			 (uint64_t)VM_KERNEL_ADDRPERM(so), outgoing, cfil_queue_len(inject_q));
#endif

	while ((data = cfil_queue_first(inject_q)) != NULL) {
		datalen = cfil_data_length(data, &mbcnt, &mbnum);

#if DATA_DEBUG
		CFIL_LOG(LOG_DEBUG, "CFIL: SERVICE INJECT-Q: <%s>: <so %llx> data %llx datalen %u (mbcnt %u)",
				 remote_addr_ptr ? "UNCONNECTED" : "CONNECTED",
				 (uint64_t)VM_KERNEL_ADDRPERM(so), (uint64_t)VM_KERNEL_ADDRPERM(data), datalen, mbcnt);
#endif

		/* Remove data from queue and adjust stats */
		cfil_queue_remove(inject_q, data, datalen);
		cfi_buf->cfi_pending_first += datalen;
		cfi_buf->cfi_pending_mbcnt -= mbcnt;
		cfi_buf->cfi_pending_mbnum -= mbnum;
		cfil_info_buf_verify(cfi_buf);

		if (outgoing) {
			error = sosend_reinject(so, NULL, data, NULL, 0);
			if (error != 0) {
#if DATA_DEBUG
				cfil_info_log(LOG_ERR, cfil_info, "CFIL: Error: sosend_reinject() failed");
				CFIL_LOG(LOG_ERR, "### sosend() failed %d", error);
#endif
				break;
			}
			// At least one injection succeeded, need to wake up pending threads.
			need_rwakeup = 1;
		} else {
			data->m_flags |= M_SKIPCFIL;

			/*
			 * NOTE: We currently only support TCP and UDP.
			 * For RAWIP, MPTCP and message TCP we'll
			 * need to call the appropriate sbappendxxx()
			 * of fix sock_inject_data_in()
			 */
			if (IS_UDP(so) == TRUE) {
				if (sbappendchain(&so->so_rcv, data, 0))
					need_rwakeup = 1;
			} else {
				if (sbappendstream(&so->so_rcv, data))
					need_rwakeup = 1;
			}
		}

		if (outgoing)
			OSAddAtomic64(datalen,
				&cfil_stats.cfs_inject_q_out_passed);
		else
			OSAddAtomic64(datalen,
				&cfil_stats.cfs_inject_q_in_passed);

		count++;
	}

#if DATA_DEBUG | VERDICT_DEBUG
	CFIL_LOG(LOG_ERR, "CFIL: SERVICE INJECT-Q: <so %llx> injected %d",
			 (uint64_t)VM_KERNEL_ADDRPERM(so), count);
#endif

	/* A single wakeup is for several packets is more efficient */
	if (need_rwakeup) {
		if (outgoing == TRUE)
			sowwakeup(so);
		else
			sorwakeup(so);
	}

	if (error != 0 && cfil_info) {
		if (error == ENOBUFS)
			OSIncrementAtomic(&cfil_stats.cfs_inject_q_nobufs);
		if (error == ENOMEM)
			OSIncrementAtomic(&cfil_stats.cfs_inject_q_nomem);

		if (outgoing) {
			cfil_info->cfi_flags |= CFIF_RETRY_INJECT_OUT;
			OSIncrementAtomic(&cfil_stats.cfs_inject_q_out_fail);
		} else {
			cfil_info->cfi_flags |= CFIF_RETRY_INJECT_IN;
			OSIncrementAtomic(&cfil_stats.cfs_inject_q_in_fail);
		}
	}

	/*
	 * Notify
	 */
	if (cfil_info && (cfil_info->cfi_flags & CFIF_SHUT_WR)) {
		cfil_sock_notify_shutdown(so, SHUT_WR);
		if (cfil_sock_data_pending(&so->so_snd) == 0)
			soshutdownlock_final(so, SHUT_WR);
	}
	if (cfil_info && (cfil_info->cfi_flags & CFIF_CLOSE_WAIT)) {
		if (cfil_filters_attached(so) == 0) {
			CFIL_LOG(LOG_INFO, "so %llx waking",
				(uint64_t)VM_KERNEL_ADDRPERM(so));
			wakeup((caddr_t)cfil_info);
		}
	}

	CFIL_INFO_VERIFY(cfil_info);

	return (error);
}
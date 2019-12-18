#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint64_t ;
typedef  int uint32_t ;
struct socket {int dummy; } ;
typedef  struct socket mbuf ;
struct cfil_info {int cfi_flags; struct cfil_entry* cfi_entries; } ;
struct TYPE_6__ {unsigned int q_start; } ;
struct cfe_buf {unsigned int cfe_pass_offset; unsigned int cfe_peeked; unsigned int cfe_peek_offset; TYPE_2__ cfe_ctl_q; int /*<<< orphan*/  cfe_pending_q; } ;
struct cfil_entry {int cfe_flags; struct cfe_buf cfe_rcv; struct cfe_buf cfe_snd; } ;
typedef  scalar_t__ errno_t ;
struct TYPE_5__ {int /*<<< orphan*/  cfs_ctl_q_in_peeked; int /*<<< orphan*/  cfs_ctl_q_out_peeked; int /*<<< orphan*/  cfs_pending_q_in_enqueued; int /*<<< orphan*/  cfs_pending_q_out_enqueued; int /*<<< orphan*/  cfs_ctl_q_not_started; } ;

/* Variables and functions */
 int CFEF_DATA_START ; 
 int CFEF_SENT_DISCONNECT_IN ; 
 int CFEF_SENT_DISCONNECT_OUT ; 
 int CFEF_SENT_SOCK_ATTACHED ; 
 int CFIF_SHUT_RD ; 
 int CFIF_SHUT_WR ; 
 int /*<<< orphan*/  CFIL_INFO_VERIFY (struct cfil_info*) ; 
 int /*<<< orphan*/  CFIL_LOG (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 scalar_t__ ENOBUFS ; 
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  OSAddAtomic64 (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSIncrementAtomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ VM_KERNEL_ADDRPERM (struct socket*) ; 
 unsigned int cfil_data_length (struct socket*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ cfil_dispatch_attach_event (struct socket*,struct cfil_info*,int) ; 
 scalar_t__ cfil_dispatch_data_event (struct socket*,struct cfil_info*,int,int,struct socket*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  cfil_dispatch_disconnect_event (struct socket*,struct cfil_info*,int,int) ; 
 int /*<<< orphan*/  cfil_queue_enqueue (int /*<<< orphan*/ *,struct socket*,unsigned int) ; 
 struct socket* cfil_queue_first (TYPE_2__*) ; 
 struct socket* cfil_queue_next (TYPE_2__*,struct socket*) ; 
 int /*<<< orphan*/  cfil_queue_remove (TYPE_2__*,struct socket*,unsigned int) ; 
 scalar_t__ cfil_service_pending_queue (struct socket*,struct cfil_info*,int,int) ; 
 TYPE_1__ cfil_stats ; 
 int /*<<< orphan*/  socket_lock_assert_owned (struct socket*) ; 

__attribute__((used)) static int
cfil_data_service_ctl_q(struct socket *so, struct cfil_info *cfil_info, uint32_t kcunit, int outgoing)
{
	errno_t error = 0;
	struct mbuf *data, *tmp = NULL;
	unsigned int datalen = 0, copylen = 0, copyoffset = 0;
	struct cfil_entry *entry;
	struct cfe_buf *entrybuf;
	uint64_t currentoffset = 0;

	if (cfil_info == NULL)
		return (0);

	CFIL_LOG(LOG_INFO, "so %llx kcunit %u outgoing %d",
		(uint64_t)VM_KERNEL_ADDRPERM(so), kcunit, outgoing);

	socket_lock_assert_owned(so);

	entry = &cfil_info->cfi_entries[kcunit - 1];
	if (outgoing)
		entrybuf = &entry->cfe_snd;
	else
		entrybuf = &entry->cfe_rcv;

	/* Send attached message if not yet done */
	if ((entry->cfe_flags & CFEF_SENT_SOCK_ATTACHED) == 0) {
		error = cfil_dispatch_attach_event(so, cfil_info, kcunit);
		if (error != 0) {
			/* We can recover from flow control */
			if (error == ENOBUFS || error == ENOMEM)
				error = 0;
			goto done;
		}
	} else if ((entry->cfe_flags & CFEF_DATA_START) == 0) {
		OSIncrementAtomic(&cfil_stats.cfs_ctl_q_not_started);
		goto done;
	}

#if DATA_DEBUG
	CFIL_LOG(LOG_DEBUG, "CFIL: SERVICE CTL-Q: pass_offset %llu peeked %llu peek_offset %llu",
		entrybuf->cfe_pass_offset,
		entrybuf->cfe_peeked,
		entrybuf->cfe_peek_offset);
#endif

	/* Move all data that can pass */
	while ((data = cfil_queue_first(&entrybuf->cfe_ctl_q)) != NULL &&
		entrybuf->cfe_ctl_q.q_start < entrybuf->cfe_pass_offset) {
		datalen = cfil_data_length(data, NULL, NULL);
		tmp = data;

		if (entrybuf->cfe_ctl_q.q_start + datalen <=
			entrybuf->cfe_pass_offset) {
			/*
			 * The first mbuf can fully pass
			 */
			copylen = datalen;
		} else {
			/*
			 * The first mbuf can partially pass
			 */
			copylen = entrybuf->cfe_pass_offset -
				entrybuf->cfe_ctl_q.q_start;
		}
		VERIFY(copylen <= datalen);

#if DATA_DEBUG
		CFIL_LOG(LOG_DEBUG,
				 "CFIL: SERVICE CTL-Q PASSING: %llx first %llu peeked %llu pass %llu peek %llu"
				 "datalen %u copylen %u",
				 (uint64_t)VM_KERNEL_ADDRPERM(tmp),
				 entrybuf->cfe_ctl_q.q_start,
				 entrybuf->cfe_peeked,
				 entrybuf->cfe_pass_offset,
				 entrybuf->cfe_peek_offset,
				 datalen, copylen);
#endif

		/*
		 * Data that passes has been peeked at explicitly or
		 * implicitly
		 */
		if (entrybuf->cfe_ctl_q.q_start + copylen >
			entrybuf->cfe_peeked)
			entrybuf->cfe_peeked =
				entrybuf->cfe_ctl_q.q_start + copylen;
		/*
		 * Stop on partial pass
		 */
		if (copylen < datalen)
			break;

		/* All good, move full data from ctl queue to pending queue */
		cfil_queue_remove(&entrybuf->cfe_ctl_q, data, datalen);

		cfil_queue_enqueue(&entrybuf->cfe_pending_q, data, datalen);
		if (outgoing)
			OSAddAtomic64(datalen,
				&cfil_stats.cfs_pending_q_out_enqueued);
		else
			OSAddAtomic64(datalen,
				&cfil_stats.cfs_pending_q_in_enqueued);
	}
	CFIL_INFO_VERIFY(cfil_info);
	if (tmp != NULL)
		CFIL_LOG(LOG_DEBUG,
			"%llx first %llu peeked %llu pass %llu peek %llu"
			"datalen %u copylen %u",
			(uint64_t)VM_KERNEL_ADDRPERM(tmp),
			entrybuf->cfe_ctl_q.q_start,
			entrybuf->cfe_peeked,
			entrybuf->cfe_pass_offset,
			entrybuf->cfe_peek_offset,
			datalen, copylen);
	tmp = NULL;

	/* Now deal with remaining data the filter wants to peek at */
	for (data = cfil_queue_first(&entrybuf->cfe_ctl_q),
		currentoffset = entrybuf->cfe_ctl_q.q_start;
		data != NULL && currentoffset < entrybuf->cfe_peek_offset;
		data = cfil_queue_next(&entrybuf->cfe_ctl_q, data),
		currentoffset += datalen) {
		datalen = cfil_data_length(data, NULL, NULL);
		tmp = data;

		/* We've already peeked at this mbuf */
		if (currentoffset + datalen <= entrybuf->cfe_peeked)
			continue;
		/*
		 * The data in the first mbuf may have been
		 * partially peeked at
		 */
		copyoffset = entrybuf->cfe_peeked - currentoffset;
		VERIFY(copyoffset < datalen);
		copylen = datalen - copyoffset;
		VERIFY(copylen <= datalen);
		/*
		 * Do not copy more than needed
		 */
		if (currentoffset + copyoffset + copylen >
			entrybuf->cfe_peek_offset) {
			copylen = entrybuf->cfe_peek_offset -
				(currentoffset + copyoffset);
		}

#if DATA_DEBUG
		CFIL_LOG(LOG_DEBUG,
				 "CFIL: SERVICE CTL-Q PEEKING: %llx current %llu peeked %llu pass %llu peek %llu "
				 "datalen %u copylen %u copyoffset %u",
				 (uint64_t)VM_KERNEL_ADDRPERM(tmp),
				 currentoffset,
				 entrybuf->cfe_peeked,
				 entrybuf->cfe_pass_offset,
				 entrybuf->cfe_peek_offset,
				 datalen, copylen, copyoffset);
#endif

		/*
		 * Stop if there is nothing more to peek at
		 */
		if (copylen == 0)
			break;
		/*
		 * Let the filter get a peek at this span of data
		 */
		error = cfil_dispatch_data_event(so, cfil_info, kcunit,
			outgoing, data, copyoffset, copylen);
		if (error != 0) {
			/* On error, leave data in ctl_q */
			break;
		}
		entrybuf->cfe_peeked += copylen;
		if (outgoing)
			OSAddAtomic64(copylen,
				&cfil_stats.cfs_ctl_q_out_peeked);
		else
			OSAddAtomic64(copylen,
				&cfil_stats.cfs_ctl_q_in_peeked);

		/* Stop when data could not be fully peeked at */
		if (copylen + copyoffset < datalen)
			break;
	}
	CFIL_INFO_VERIFY(cfil_info);
	if (tmp != NULL)
		CFIL_LOG(LOG_DEBUG,
			"%llx first %llu peeked %llu pass %llu peek %llu"
			"datalen %u copylen %u copyoffset %u",
			(uint64_t)VM_KERNEL_ADDRPERM(tmp),
			currentoffset,
			entrybuf->cfe_peeked,
			entrybuf->cfe_pass_offset,
			entrybuf->cfe_peek_offset,
			datalen, copylen, copyoffset);

	/*
	 * Process data that has passed the filter
	 */
	error = cfil_service_pending_queue(so, cfil_info, kcunit, outgoing);
	if (error != 0) {
		CFIL_LOG(LOG_ERR, "cfil_service_pending_queue() error %d",
			error);
		goto done;
	}

	/*
	 * Dispatch disconnect events that could not be sent
	 */
	if (cfil_info == NULL)
		goto done;
	else if (outgoing) {
		if ((cfil_info->cfi_flags & CFIF_SHUT_WR) &&
		    !(entry->cfe_flags & CFEF_SENT_DISCONNECT_OUT))
			cfil_dispatch_disconnect_event(so, cfil_info, kcunit, 1);
	} else {
		if ((cfil_info->cfi_flags & CFIF_SHUT_RD) &&
		    !(entry->cfe_flags & CFEF_SENT_DISCONNECT_IN))
			cfil_dispatch_disconnect_event(so, cfil_info, kcunit, 0);
	}

done:
	CFIL_LOG(LOG_DEBUG,
		"first %llu peeked %llu pass %llu peek %llu",
		entrybuf->cfe_ctl_q.q_start,
		entrybuf->cfe_peeked,
		entrybuf->cfe_pass_offset,
		entrybuf->cfe_peek_offset);

	CFIL_INFO_VERIFY(cfil_info);
	return (error);
}
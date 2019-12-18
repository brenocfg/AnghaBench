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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct sctp_chunk {int singleton; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  frag_list; int /*<<< orphan*/  transmitted_list; int /*<<< orphan*/ * msg; int /*<<< orphan*/  fast_retransmit; scalar_t__ tsn_gap_acked; scalar_t__ tsn_missing_report; scalar_t__ pdiscard; scalar_t__ ecn_ce_done; scalar_t__ end_of_packet; scalar_t__ sent_at; scalar_t__ rtt_in_progress; scalar_t__ has_ssn; scalar_t__ has_tsn; struct sctp_association* asoc; struct sk_buff* skb; int /*<<< orphan*/  list; } ;
struct sctp_association {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCTP_CAN_FRTX ; 
 int /*<<< orphan*/  SCTP_DBG_OBJCNT_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_DEBUG_PRINTK (char*,struct sk_buff*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  chunk ; 
 struct sctp_chunk* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_chunk_cachep ; 

struct sctp_chunk *sctp_chunkify(struct sk_buff *skb,
			    const struct sctp_association *asoc,
			    struct sock *sk)
{
	struct sctp_chunk *retval;

	retval = kmem_cache_zalloc(sctp_chunk_cachep, GFP_ATOMIC);

	if (!retval)
		goto nodata;

	if (!sk) {
		SCTP_DEBUG_PRINTK("chunkifying skb %p w/o an sk\n", skb);
	}

	INIT_LIST_HEAD(&retval->list);
	retval->skb		= skb;
	retval->asoc		= (struct sctp_association *)asoc;
	retval->has_tsn		= 0;
	retval->has_ssn         = 0;
	retval->rtt_in_progress	= 0;
	retval->sent_at		= 0;
	retval->singleton	= 1;
	retval->end_of_packet	= 0;
	retval->ecn_ce_done	= 0;
	retval->pdiscard	= 0;

	/* sctpimpguide-05.txt Section 2.8.2
	 * M1) Each time a new DATA chunk is transmitted
	 * set the 'TSN.Missing.Report' count for that TSN to 0. The
	 * 'TSN.Missing.Report' count will be used to determine missing chunks
	 * and when to fast retransmit.
	 */
	retval->tsn_missing_report = 0;
	retval->tsn_gap_acked = 0;
	retval->fast_retransmit = SCTP_CAN_FRTX;

	/* If this is a fragmented message, track all fragments
	 * of the message (for SEND_FAILED).
	 */
	retval->msg = NULL;

	/* Polish the bead hole.  */
	INIT_LIST_HEAD(&retval->transmitted_list);
	INIT_LIST_HEAD(&retval->frag_list);
	SCTP_DBG_OBJCNT_INC(chunk);
	atomic_set(&retval->refcnt, 1);

nodata:
	return retval;
}
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
struct sk_buff {void* data; } ;
struct TYPE_2__ {scalar_t__ type; int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ sctp_chunkhdr_t ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 scalar_t__ SCTP_CID_ABORT ; 
 scalar_t__ SCTP_CID_INIT ; 
 scalar_t__ SCTP_CID_SHUTDOWN_COMPLETE ; 
 int WORD_ROUND (int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * skb_tail_pointer (struct sk_buff*) ; 

__attribute__((used)) static int sctp_rcv_ootb(struct sk_buff *skb)
{
	sctp_chunkhdr_t *ch;
	__u8 *ch_end;

	ch = (sctp_chunkhdr_t *) skb->data;

	/* Scan through all the chunks in the packet.  */
	do {
		/* Break out if chunk length is less then minimal. */
		if (ntohs(ch->length) < sizeof(sctp_chunkhdr_t))
			break;

		ch_end = ((__u8 *)ch) + WORD_ROUND(ntohs(ch->length));
		if (ch_end > skb_tail_pointer(skb))
			break;

		/* RFC 8.4, 2) If the OOTB packet contains an ABORT chunk, the
		 * receiver MUST silently discard the OOTB packet and take no
		 * further action.
		 */
		if (SCTP_CID_ABORT == ch->type)
			goto discard;

		/* RFC 8.4, 6) If the packet contains a SHUTDOWN COMPLETE
		 * chunk, the receiver should silently discard the packet
		 * and take no further action.
		 */
		if (SCTP_CID_SHUTDOWN_COMPLETE == ch->type)
			goto discard;

		/* RFC 4460, 2.11.2
		 * This will discard packets with INIT chunk bundled as
		 * subsequent chunks in the packet.  When INIT is first,
		 * the normal INIT processing will discard the chunk.
		 */
		if (SCTP_CID_INIT == ch->type && (void *)ch != skb->data)
			goto discard;

		ch = (sctp_chunkhdr_t *) ch_end;
	} while (ch_end < skb_tail_pointer(skb));

	return 0;

discard:
	return 1;
}
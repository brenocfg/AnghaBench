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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  truesize; } ;
struct sctp_ulpevent {int dummy; } ;
struct sctp_chunk {TYPE_1__* chunk_hdr; int /*<<< orphan*/  skb; } ;
struct sctp_association {int dummy; } ;
struct sctp_assoc_change {int /*<<< orphan*/  sac_assoc_id; void* sac_inbound_streams; void* sac_outbound_streams; void* sac_error; int /*<<< orphan*/  sac_length; scalar_t__ sac_flags; void* sac_state; int /*<<< orphan*/  sac_type; } ;
typedef  int /*<<< orphan*/  sctp_chunkhdr_t ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  void* __u16 ;
struct TYPE_2__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_NOTIFICATION ; 
 int /*<<< orphan*/  SCTP_ASSOC_CHANGE ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_assoc2id (struct sctp_association const*) ; 
 struct sk_buff* sctp_event2skb (struct sctp_ulpevent*) ; 
 struct sctp_ulpevent* sctp_skb2event (struct sk_buff*) ; 
 int /*<<< orphan*/  sctp_ulpevent_init (struct sctp_ulpevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sctp_ulpevent* sctp_ulpevent_new (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_ulpevent_set_owner (struct sctp_ulpevent*,struct sctp_association const*) ; 
 struct sk_buff* skb_copy_expand (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 
 scalar_t__ skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,scalar_t__) ; 

struct sctp_ulpevent  *sctp_ulpevent_make_assoc_change(
	const struct sctp_association *asoc,
	__u16 flags, __u16 state, __u16 error, __u16 outbound,
	__u16 inbound, struct sctp_chunk *chunk, gfp_t gfp)
{
	struct sctp_ulpevent *event;
	struct sctp_assoc_change *sac;
	struct sk_buff *skb;

	/* If the lower layer passed in the chunk, it will be
	 * an ABORT, so we need to include it in the sac_info.
	 */
	if (chunk) {
		/* Copy the chunk data to a new skb and reserve enough
		 * head room to use as notification.
		 */
		skb = skb_copy_expand(chunk->skb,
				      sizeof(struct sctp_assoc_change), 0, gfp);

		if (!skb)
			goto fail;

		/* Embed the event fields inside the cloned skb.  */
		event = sctp_skb2event(skb);
		sctp_ulpevent_init(event, MSG_NOTIFICATION, skb->truesize);

		/* Include the notification structure */
		sac = (struct sctp_assoc_change *)
			skb_push(skb, sizeof(struct sctp_assoc_change));

		/* Trim the buffer to the right length.  */
		skb_trim(skb, sizeof(struct sctp_assoc_change) +
			 ntohs(chunk->chunk_hdr->length) -
			 sizeof(sctp_chunkhdr_t));
	} else {
		event = sctp_ulpevent_new(sizeof(struct sctp_assoc_change),
				  MSG_NOTIFICATION, gfp);
		if (!event)
			goto fail;

		skb = sctp_event2skb(event);
		sac = (struct sctp_assoc_change *) skb_put(skb,
					sizeof(struct sctp_assoc_change));
	}

	/* Socket Extensions for SCTP
	 * 5.3.1.1 SCTP_ASSOC_CHANGE
	 *
	 * sac_type:
	 * It should be SCTP_ASSOC_CHANGE.
	 */
	sac->sac_type = SCTP_ASSOC_CHANGE;

	/* Socket Extensions for SCTP
	 * 5.3.1.1 SCTP_ASSOC_CHANGE
	 *
	 * sac_state: 32 bits (signed integer)
	 * This field holds one of a number of values that communicate the
	 * event that happened to the association.
	 */
	sac->sac_state = state;

	/* Socket Extensions for SCTP
	 * 5.3.1.1 SCTP_ASSOC_CHANGE
	 *
	 * sac_flags: 16 bits (unsigned integer)
	 * Currently unused.
	 */
	sac->sac_flags = 0;

	/* Socket Extensions for SCTP
	 * 5.3.1.1 SCTP_ASSOC_CHANGE
	 *
	 * sac_length: sizeof (__u32)
	 * This field is the total length of the notification data, including
	 * the notification header.
	 */
	sac->sac_length = skb->len;

	/* Socket Extensions for SCTP
	 * 5.3.1.1 SCTP_ASSOC_CHANGE
	 *
	 * sac_error:  32 bits (signed integer)
	 *
	 * If the state was reached due to a error condition (e.g.
	 * COMMUNICATION_LOST) any relevant error information is available in
	 * this field. This corresponds to the protocol error codes defined in
	 * [SCTP].
	 */
	sac->sac_error = error;

	/* Socket Extensions for SCTP
	 * 5.3.1.1 SCTP_ASSOC_CHANGE
	 *
	 * sac_outbound_streams:  16 bits (unsigned integer)
	 * sac_inbound_streams:  16 bits (unsigned integer)
	 *
	 * The maximum number of streams allowed in each direction are
	 * available in sac_outbound_streams and sac_inbound streams.
	 */
	sac->sac_outbound_streams = outbound;
	sac->sac_inbound_streams = inbound;

	/* Socket Extensions for SCTP
	 * 5.3.1.1 SCTP_ASSOC_CHANGE
	 *
	 * sac_assoc_id: sizeof (sctp_assoc_t)
	 *
	 * The association id field, holds the identifier for the association.
	 * All notifications for a given association have the same association
	 * identifier.  For TCP style socket, this field is ignored.
	 */
	sctp_ulpevent_set_owner(event, asoc);
	sac->sac_assoc_id = sctp_assoc2id(asoc);

	return event;

fail:
	return NULL;
}
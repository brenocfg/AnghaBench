#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  truesize; } ;
struct sctp_ulpevent {int dummy; } ;
struct sctp_remote_error {int /*<<< orphan*/  sre_assoc_id; int /*<<< orphan*/  sre_error; int /*<<< orphan*/  sre_length; scalar_t__ sre_flags; int /*<<< orphan*/  sre_type; } ;
struct sctp_chunk {TYPE_2__* skb; } ;
struct sctp_association {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  length; int /*<<< orphan*/  cause; } ;
typedef  TYPE_1__ sctp_errhdr_t ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  __u16 ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_5__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_NOTIFICATION ; 
 int /*<<< orphan*/  SCTP_REMOTE_ERROR ; 
 int WORD_ROUND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_assoc2id (struct sctp_association const*) ; 
 struct sctp_ulpevent* sctp_skb2event (struct sk_buff*) ; 
 int /*<<< orphan*/  sctp_ulpevent_init (struct sctp_ulpevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_ulpevent_set_owner (struct sctp_ulpevent*,struct sctp_association const*) ; 
 struct sk_buff* skb_copy_expand (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (TYPE_2__*,int) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 

struct sctp_ulpevent *sctp_ulpevent_make_remote_error(
	const struct sctp_association *asoc, struct sctp_chunk *chunk,
	__u16 flags, gfp_t gfp)
{
	struct sctp_ulpevent *event;
	struct sctp_remote_error *sre;
	struct sk_buff *skb;
	sctp_errhdr_t *ch;
	__be16 cause;
	int elen;

	ch = (sctp_errhdr_t *)(chunk->skb->data);
	cause = ch->cause;
	elen = WORD_ROUND(ntohs(ch->length)) - sizeof(sctp_errhdr_t);

	/* Pull off the ERROR header.  */
	skb_pull(chunk->skb, sizeof(sctp_errhdr_t));

	/* Copy the skb to a new skb with room for us to prepend
	 * notification with.
	 */
	skb = skb_copy_expand(chunk->skb, sizeof(struct sctp_remote_error),
			      0, gfp);

	/* Pull off the rest of the cause TLV from the chunk.  */
	skb_pull(chunk->skb, elen);
	if (!skb)
		goto fail;

	/* Embed the event fields inside the cloned skb.  */
	event = sctp_skb2event(skb);
	sctp_ulpevent_init(event, MSG_NOTIFICATION, skb->truesize);

	sre = (struct sctp_remote_error *)
		skb_push(skb, sizeof(struct sctp_remote_error));

	/* Trim the buffer to the right length.  */
	skb_trim(skb, sizeof(struct sctp_remote_error) + elen);

	/* Socket Extensions for SCTP
	 * 5.3.1.3 SCTP_REMOTE_ERROR
	 *
	 * sre_type:
	 *   It should be SCTP_REMOTE_ERROR.
	 */
	sre->sre_type = SCTP_REMOTE_ERROR;

	/*
	 * Socket Extensions for SCTP
	 * 5.3.1.3 SCTP_REMOTE_ERROR
	 *
	 * sre_flags: 16 bits (unsigned integer)
	 *   Currently unused.
	 */
	sre->sre_flags = 0;

	/* Socket Extensions for SCTP
	 * 5.3.1.3 SCTP_REMOTE_ERROR
	 *
	 * sre_length: sizeof (__u32)
	 *
	 * This field is the total length of the notification data,
	 * including the notification header.
	 */
	sre->sre_length = skb->len;

	/* Socket Extensions for SCTP
	 * 5.3.1.3 SCTP_REMOTE_ERROR
	 *
	 * sre_error: 16 bits (unsigned integer)
	 * This value represents one of the Operational Error causes defined in
	 * the SCTP specification, in network byte order.
	 */
	sre->sre_error = cause;

	/* Socket Extensions for SCTP
	 * 5.3.1.3 SCTP_REMOTE_ERROR
	 *
	 * sre_assoc_id: sizeof (sctp_assoc_t)
	 *
	 * The association id field, holds the identifier for the association.
	 * All notifications for a given association have the same association
	 * identifier.  For TCP style socket, this field is ignored.
	 */
	sctp_ulpevent_set_owner(event, asoc);
	sre->sre_assoc_id = sctp_assoc2id(asoc);

	return event;

fail:
	return NULL;
}
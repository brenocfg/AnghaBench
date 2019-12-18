#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  truesize; } ;
struct sctp_ulpevent {int dummy; } ;
struct sctp_sndrcvinfo {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  sinfo_flags; } ;
struct sctp_send_failed {int ssf_length; int /*<<< orphan*/  ssf_assoc_id; TYPE_2__ ssf_info; int /*<<< orphan*/  ssf_error; int /*<<< orphan*/  ssf_flags; int /*<<< orphan*/  ssf_type; } ;
struct sctp_data_chunk {int dummy; } ;
struct sctp_chunk {TYPE_1__* chunk_hdr; int /*<<< orphan*/  sinfo; int /*<<< orphan*/  skb; } ;
struct sctp_association {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_3__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_NOTIFICATION ; 
 int /*<<< orphan*/  SCTP_SEND_FAILED ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_assoc2id (struct sctp_association const*) ; 
 struct sctp_ulpevent* sctp_skb2event (struct sk_buff*) ; 
 int /*<<< orphan*/  sctp_ulpevent_init (struct sctp_ulpevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_ulpevent_set_owner (struct sctp_ulpevent*,struct sctp_association const*) ; 
 struct sk_buff* skb_copy_expand (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 

struct sctp_ulpevent *sctp_ulpevent_make_send_failed(
	const struct sctp_association *asoc, struct sctp_chunk *chunk,
	__u16 flags, __u32 error, gfp_t gfp)
{
	struct sctp_ulpevent *event;
	struct sctp_send_failed *ssf;
	struct sk_buff *skb;

	/* Pull off any padding. */
	int len = ntohs(chunk->chunk_hdr->length);

	/* Make skb with more room so we can prepend notification.  */
	skb = skb_copy_expand(chunk->skb,
			      sizeof(struct sctp_send_failed), /* headroom */
			      0,                               /* tailroom */
			      gfp);
	if (!skb)
		goto fail;

	/* Pull off the common chunk header and DATA header.  */
	skb_pull(skb, sizeof(struct sctp_data_chunk));
	len -= sizeof(struct sctp_data_chunk);

	/* Embed the event fields inside the cloned skb.  */
	event = sctp_skb2event(skb);
	sctp_ulpevent_init(event, MSG_NOTIFICATION, skb->truesize);

	ssf = (struct sctp_send_failed *)
		skb_push(skb, sizeof(struct sctp_send_failed));

	/* Socket Extensions for SCTP
	 * 5.3.1.4 SCTP_SEND_FAILED
	 *
	 * ssf_type:
	 * It should be SCTP_SEND_FAILED.
	 */
	ssf->ssf_type = SCTP_SEND_FAILED;

	/* Socket Extensions for SCTP
	 * 5.3.1.4 SCTP_SEND_FAILED
	 *
	 * ssf_flags: 16 bits (unsigned integer)
	 * The flag value will take one of the following values
	 *
	 * SCTP_DATA_UNSENT - Indicates that the data was never put on
	 *                    the wire.
	 *
	 * SCTP_DATA_SENT   - Indicates that the data was put on the wire.
	 *                    Note that this does not necessarily mean that the
	 *                    data was (or was not) successfully delivered.
	 */
	ssf->ssf_flags = flags;

	/* Socket Extensions for SCTP
	 * 5.3.1.4 SCTP_SEND_FAILED
	 *
	 * ssf_length: sizeof (__u32)
	 * This field is the total length of the notification data, including
	 * the notification header.
	 */
	ssf->ssf_length = sizeof(struct sctp_send_failed) + len;
	skb_trim(skb, ssf->ssf_length);

	/* Socket Extensions for SCTP
	 * 5.3.1.4 SCTP_SEND_FAILED
	 *
	 * ssf_error: 16 bits (unsigned integer)
	 * This value represents the reason why the send failed, and if set,
	 * will be a SCTP protocol error code as defined in [SCTP] section
	 * 3.3.10.
	 */
	ssf->ssf_error = error;

	/* Socket Extensions for SCTP
	 * 5.3.1.4 SCTP_SEND_FAILED
	 *
	 * ssf_info: sizeof (struct sctp_sndrcvinfo)
	 * The original send information associated with the undelivered
	 * message.
	 */
	memcpy(&ssf->ssf_info, &chunk->sinfo, sizeof(struct sctp_sndrcvinfo));

	/* Per TSVWG discussion with Randy. Allow the application to
	 * ressemble a fragmented message.
	 */
	ssf->ssf_info.sinfo_flags = chunk->chunk_hdr->flags;

	/* Socket Extensions for SCTP
	 * 5.3.1.4 SCTP_SEND_FAILED
	 *
	 * ssf_assoc_id: sizeof (sctp_assoc_t)
	 * The association id field, sf_assoc_id, holds the identifier for the
	 * association.  All notifications for a given association have the
	 * same association identifier.  For TCP style socket, this field is
	 * ignored.
	 */
	sctp_ulpevent_set_owner(event, asoc);
	ssf->ssf_assoc_id = sctp_assoc2id(asoc);
	return event;

fail:
	return NULL;
}
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
struct sk_buff {int dummy; } ;
struct sctp_ulpevent {int dummy; } ;
struct sctp_shutdown_event {int sse_length; int /*<<< orphan*/  sse_assoc_id; scalar_t__ sse_flags; int /*<<< orphan*/  sse_type; } ;
struct sctp_association {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_NOTIFICATION ; 
 int /*<<< orphan*/  SCTP_SHUTDOWN_EVENT ; 
 int /*<<< orphan*/  sctp_assoc2id (struct sctp_association const*) ; 
 struct sk_buff* sctp_event2skb (struct sctp_ulpevent*) ; 
 struct sctp_ulpevent* sctp_ulpevent_new (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_ulpevent_set_owner (struct sctp_ulpevent*,struct sctp_association const*) ; 
 scalar_t__ skb_put (struct sk_buff*,int) ; 

struct sctp_ulpevent *sctp_ulpevent_make_shutdown_event(
	const struct sctp_association *asoc,
	__u16 flags, gfp_t gfp)
{
	struct sctp_ulpevent *event;
	struct sctp_shutdown_event *sse;
	struct sk_buff *skb;

	event = sctp_ulpevent_new(sizeof(struct sctp_shutdown_event),
				  MSG_NOTIFICATION, gfp);
	if (!event)
		goto fail;

	skb = sctp_event2skb(event);
	sse = (struct sctp_shutdown_event *)
		skb_put(skb, sizeof(struct sctp_shutdown_event));

	/* Socket Extensions for SCTP
	 * 5.3.1.5 SCTP_SHUTDOWN_EVENT
	 *
	 * sse_type
	 * It should be SCTP_SHUTDOWN_EVENT
	 */
	sse->sse_type = SCTP_SHUTDOWN_EVENT;

	/* Socket Extensions for SCTP
	 * 5.3.1.5 SCTP_SHUTDOWN_EVENT
	 *
	 * sse_flags: 16 bits (unsigned integer)
	 * Currently unused.
	 */
	sse->sse_flags = 0;

	/* Socket Extensions for SCTP
	 * 5.3.1.5 SCTP_SHUTDOWN_EVENT
	 *
	 * sse_length: sizeof (__u32)
	 * This field is the total length of the notification data, including
	 * the notification header.
	 */
	sse->sse_length = sizeof(struct sctp_shutdown_event);

	/* Socket Extensions for SCTP
	 * 5.3.1.5 SCTP_SHUTDOWN_EVENT
	 *
	 * sse_assoc_id: sizeof (sctp_assoc_t)
	 * The association id field, holds the identifier for the association.
	 * All notifications for a given association have the same association
	 * identifier.  For TCP style socket, this field is ignored.
	 */
	sctp_ulpevent_set_owner(event, asoc);
	sse->sse_assoc_id = sctp_assoc2id(asoc);

	return event;

fail:
	return NULL;
}
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
struct sctp_ulpevent {TYPE_1__* asoc; int /*<<< orphan*/  cumtsn; int /*<<< orphan*/  tsn; int /*<<< orphan*/  flags; int /*<<< orphan*/  ppid; int /*<<< orphan*/  ssn; int /*<<< orphan*/  stream; } ;
struct sctp_sndrcvinfo {scalar_t__ sinfo_timetolive; int /*<<< orphan*/  sinfo_context; int /*<<< orphan*/  sinfo_assoc_id; int /*<<< orphan*/  sinfo_cumtsn; int /*<<< orphan*/  sinfo_tsn; int /*<<< orphan*/  sinfo_flags; int /*<<< orphan*/  sinfo_ppid; int /*<<< orphan*/  sinfo_ssn; int /*<<< orphan*/  sinfo_stream; } ;
struct msghdr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  default_rcv_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_SCTP ; 
 int /*<<< orphan*/  SCTP_SNDRCV ; 
 int /*<<< orphan*/  put_cmsg (struct msghdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/  sctp_assoc2id (TYPE_1__*) ; 
 scalar_t__ sctp_ulpevent_is_notification (struct sctp_ulpevent const*) ; 

void sctp_ulpevent_read_sndrcvinfo(const struct sctp_ulpevent *event,
				   struct msghdr *msghdr)
{
	struct sctp_sndrcvinfo sinfo;

	if (sctp_ulpevent_is_notification(event))
		return;

	/* Sockets API Extensions for SCTP
	 * Section 5.2.2 SCTP Header Information Structure (SCTP_SNDRCV)
	 *
	 * sinfo_stream: 16 bits (unsigned integer)
	 *
	 * For recvmsg() the SCTP stack places the message's stream number in
	 * this value.
	*/
	sinfo.sinfo_stream = event->stream;
	/* sinfo_ssn: 16 bits (unsigned integer)
	 *
	 * For recvmsg() this value contains the stream sequence number that
	 * the remote endpoint placed in the DATA chunk.  For fragmented
	 * messages this is the same number for all deliveries of the message
	 * (if more than one recvmsg() is needed to read the message).
	 */
	sinfo.sinfo_ssn = event->ssn;
	/* sinfo_ppid: 32 bits (unsigned integer)
	 *
	 * In recvmsg() this value is
	 * the same information that was passed by the upper layer in the peer
	 * application.  Please note that byte order issues are NOT accounted
	 * for and this information is passed opaquely by the SCTP stack from
	 * one end to the other.
	 */
	sinfo.sinfo_ppid = event->ppid;
	/* sinfo_flags: 16 bits (unsigned integer)
	 *
	 * This field may contain any of the following flags and is composed of
	 * a bitwise OR of these values.
	 *
	 * recvmsg() flags:
	 *
	 * SCTP_UNORDERED - This flag is present when the message was sent
	 *                 non-ordered.
	 */
	sinfo.sinfo_flags = event->flags;
	/* sinfo_tsn: 32 bit (unsigned integer)
	 *
	 * For the receiving side, this field holds a TSN that was
	 * assigned to one of the SCTP Data Chunks.
	 */
	sinfo.sinfo_tsn = event->tsn;
	/* sinfo_cumtsn: 32 bit (unsigned integer)
	 *
	 * This field will hold the current cumulative TSN as
	 * known by the underlying SCTP layer.  Note this field is
	 * ignored when sending and only valid for a receive
	 * operation when sinfo_flags are set to SCTP_UNORDERED.
	 */
	sinfo.sinfo_cumtsn = event->cumtsn;
	/* sinfo_assoc_id: sizeof (sctp_assoc_t)
	 *
	 * The association handle field, sinfo_assoc_id, holds the identifier
	 * for the association announced in the COMMUNICATION_UP notification.
	 * All notifications for a given association have the same identifier.
	 * Ignored for one-to-one style sockets.
	 */
	sinfo.sinfo_assoc_id = sctp_assoc2id(event->asoc);

	/* context value that is set via SCTP_CONTEXT socket option. */
	sinfo.sinfo_context = event->asoc->default_rcv_context;

	/* These fields are not used while receiving. */
	sinfo.sinfo_timetolive = 0;

	put_cmsg(msghdr, IPPROTO_SCTP, SCTP_SNDRCV,
		 sizeof(struct sctp_sndrcvinfo), (void *)&sinfo);
}
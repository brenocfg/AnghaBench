#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct sctp_transport {size_t flight_size; struct sctp_association* asoc; } ;
struct sctp_packet {struct sctp_transport* transport; } ;
struct sctp_chunk {TYPE_3__* msg; } ;
struct TYPE_5__ {size_t rwnd; int /*<<< orphan*/  prsctp_capable; } ;
struct TYPE_4__ {size_t outstanding_bytes; } ;
struct sctp_association {TYPE_2__ peer; TYPE_1__ outqueue; } ;
struct TYPE_6__ {scalar_t__ can_abandon; } ;

/* Variables and functions */
 int /*<<< orphan*/  sctp_chunk_assign_ssn (struct sctp_chunk*) ; 
 int /*<<< orphan*/  sctp_chunk_assign_tsn (struct sctp_chunk*) ; 
 size_t sctp_data_size (struct sctp_chunk*) ; 

__attribute__((used)) static void sctp_packet_append_data(struct sctp_packet *packet,
				struct sctp_chunk *chunk)
{
	struct sctp_transport *transport = packet->transport;
	size_t datasize = sctp_data_size(chunk);
	struct sctp_association *asoc = transport->asoc;
	u32 rwnd = asoc->peer.rwnd;

	/* Keep track of how many bytes are in flight over this transport. */
	transport->flight_size += datasize;

	/* Keep track of how many bytes are in flight to the receiver. */
	asoc->outqueue.outstanding_bytes += datasize;

	/* Update our view of the receiver's rwnd. */
	if (datasize < rwnd)
		rwnd -= datasize;
	else
		rwnd = 0;

	asoc->peer.rwnd = rwnd;
	/* Has been accepted for transmission. */
	if (!asoc->peer.prsctp_capable)
		chunk->msg->can_abandon = 0;
	sctp_chunk_assign_tsn(chunk);
	sctp_chunk_assign_ssn(chunk);
}
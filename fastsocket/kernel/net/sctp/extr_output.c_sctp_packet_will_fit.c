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
typedef  size_t u16 ;
struct sctp_packet {size_t size; int ipfragok; int /*<<< orphan*/  has_data; TYPE_1__* transport; } ;
struct sctp_chunk {scalar_t__ auth; } ;
typedef  int /*<<< orphan*/  sctp_xmit_t ;
struct TYPE_4__ {size_t pathmtu; } ;
struct TYPE_3__ {size_t pathmtu; TYPE_2__* asoc; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_XMIT_OK ; 
 int /*<<< orphan*/  SCTP_XMIT_PMTU_FULL ; 
 int /*<<< orphan*/  sctp_chunk_is_data (struct sctp_chunk*) ; 
 scalar_t__ sctp_packet_empty (struct sctp_packet*) ; 

__attribute__((used)) static sctp_xmit_t sctp_packet_will_fit(struct sctp_packet *packet,
					struct sctp_chunk *chunk,
					u16 chunk_len)
{
	size_t psize;
	size_t pmtu;
	int too_big;
	sctp_xmit_t retval = SCTP_XMIT_OK;

	psize = packet->size;
	pmtu  = ((packet->transport->asoc) ?
		(packet->transport->asoc->pathmtu) :
		(packet->transport->pathmtu));

	too_big = (psize + chunk_len > pmtu);

	/* Decide if we need to fragment or resubmit later. */
	if (too_big) {
		/* It's OK to fragmet at IP level if any one of the following
		 * is true:
		 * 	1. The packet is empty (meaning this chunk is greater
		 * 	   the MTU)
		 * 	2. The chunk we are adding is a control chunk
		 * 	3. The packet doesn't have any data in it yet and data
		 * 	requires authentication.
		 */
		if (sctp_packet_empty(packet) || !sctp_chunk_is_data(chunk) ||
		    (!packet->has_data && chunk->auth)) {
			/* We no longer do re-fragmentation.
			 * Just fragment at the IP layer, if we
			 * actually hit this condition
			 */
			packet->ipfragok = 1;
		} else {
			retval = SCTP_XMIT_PMTU_FULL;
		}
	}

	return retval;
}
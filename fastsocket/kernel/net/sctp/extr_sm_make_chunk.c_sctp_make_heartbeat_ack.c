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
struct TYPE_2__ {int /*<<< orphan*/  hbs_hdr; } ;
struct sctp_chunk {int /*<<< orphan*/  transport; TYPE_1__ subh; } ;
struct sctp_association {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_CID_HEARTBEAT_ACK ; 
 int /*<<< orphan*/  sctp_addto_chunk (struct sctp_chunk*,size_t const,void const*) ; 
 struct sctp_chunk* sctp_make_chunk (struct sctp_association const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t const) ; 

struct sctp_chunk *sctp_make_heartbeat_ack(const struct sctp_association *asoc,
				      const struct sctp_chunk *chunk,
				      const void *payload, const size_t paylen)
{
	struct sctp_chunk *retval;

	retval  = sctp_make_chunk(asoc, SCTP_CID_HEARTBEAT_ACK, 0, paylen);
	if (!retval)
		goto nodata;

	retval->subh.hbs_hdr = sctp_addto_chunk(retval, paylen, payload);

	/* RFC 2960 6.4 Multi-homed SCTP Endpoints
	 *
	 * An endpoint SHOULD transmit reply chunks (e.g., SACK,
	 * HEARTBEAT ACK, * etc.) to the same destination transport
	 * address from which it * received the DATA or control chunk
	 * to which it is replying.
	 *
	 * [HBACK back to where the HEARTBEAT came from.]
	 */
	if (chunk)
		retval->transport = chunk->transport;

nodata:
	return retval;
}
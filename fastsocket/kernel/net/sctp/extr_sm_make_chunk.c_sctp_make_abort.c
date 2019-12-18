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
struct sctp_chunk {int /*<<< orphan*/  transport; TYPE_1__* chunk_hdr; } ;
struct sctp_association {int dummy; } ;
typedef  scalar_t__ __u8 ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ SCTP_CHUNK_FLAG_T ; 
 int /*<<< orphan*/  SCTP_CID_ABORT ; 
 scalar_t__ SCTP_CID_INIT ; 
 struct sctp_chunk* sctp_make_chunk (struct sctp_association const*,int /*<<< orphan*/ ,scalar_t__,size_t const) ; 

struct sctp_chunk *sctp_make_abort(const struct sctp_association *asoc,
			      const struct sctp_chunk *chunk,
			      const size_t hint)
{
	struct sctp_chunk *retval;
	__u8 flags = 0;

	/* Set the T-bit if we have no association and 'chunk' is not
	 * an INIT (vtag will be reflected).
	 */
	if (!asoc) {
		if (chunk && chunk->chunk_hdr &&
		    chunk->chunk_hdr->type == SCTP_CID_INIT)
			flags = 0;
		else
			flags = SCTP_CHUNK_FLAG_T;
	}

	retval = sctp_make_chunk(asoc, SCTP_CID_ABORT, flags, hint);

	/* RFC 2960 6.4 Multi-homed SCTP Endpoints
	 *
	 * An endpoint SHOULD transmit reply chunks (e.g., SACK,
	 * HEARTBEAT ACK, * etc.) to the same destination transport
	 * address from which it * received the DATA or control chunk
	 * to which it is replying.
	 *
	 * [ABORT back to where the offender came from.]
	 */
	if (retval && chunk)
		retval->transport = chunk->transport;

	return retval;
}
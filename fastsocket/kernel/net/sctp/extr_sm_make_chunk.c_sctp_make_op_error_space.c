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
struct sctp_chunk {int /*<<< orphan*/  transport; } ;
struct sctp_association {int dummy; } ;
typedef  int /*<<< orphan*/  sctp_errhdr_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_CID_ERROR ; 
 struct sctp_chunk* sctp_make_chunk (struct sctp_association const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct sctp_chunk *sctp_make_op_error_space(
	const struct sctp_association *asoc,
	const struct sctp_chunk *chunk,
	size_t size)
{
	struct sctp_chunk *retval;

	retval = sctp_make_chunk(asoc, SCTP_CID_ERROR, 0,
				 sizeof(sctp_errhdr_t) + size);
	if (!retval)
		goto nodata;

	/* RFC 2960 6.4 Multi-homed SCTP Endpoints
	 *
	 * An endpoint SHOULD transmit reply chunks (e.g., SACK,
	 * HEARTBEAT ACK, etc.) to the same destination transport
	 * address from which it received the DATA or control chunk
	 * to which it is replying.
	 *
	 */
	if (chunk)
		retval->transport = chunk->transport;

nodata:
	return retval;
}
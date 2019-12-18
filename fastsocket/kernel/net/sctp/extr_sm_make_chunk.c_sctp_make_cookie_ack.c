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

/* Variables and functions */
 int /*<<< orphan*/  SCTP_CID_COOKIE_ACK ; 
 struct sctp_chunk* sctp_make_chunk (struct sctp_association const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct sctp_chunk *sctp_make_cookie_ack(const struct sctp_association *asoc,
				   const struct sctp_chunk *chunk)
{
	struct sctp_chunk *retval;

	retval = sctp_make_chunk(asoc, SCTP_CID_COOKIE_ACK, 0, 0);

	/* RFC 2960 6.4 Multi-homed SCTP Endpoints
	 *
	 * An endpoint SHOULD transmit reply chunks (e.g., SACK,
	 * HEARTBEAT ACK, * etc.) to the same destination transport
	 * address from which it * received the DATA or control chunk
	 * to which it is replying.
	 *
	 * [COOKIE ACK back to where the COOKIE ECHO came from.]
	 */
	if (retval && chunk)
		retval->transport = chunk->transport;

	return retval;
}
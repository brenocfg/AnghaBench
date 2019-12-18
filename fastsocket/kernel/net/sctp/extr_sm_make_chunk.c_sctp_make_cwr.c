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
struct TYPE_4__ {int /*<<< orphan*/  ecn_cwr_hdr; } ;
struct sctp_chunk {int /*<<< orphan*/  transport; TYPE_1__ subh; } ;
struct sctp_association {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  lowest_tsn; } ;
typedef  TYPE_2__ sctp_cwrhdr_t ;
typedef  int /*<<< orphan*/  cwr ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_CID_ECN_CWR ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  sctp_addto_chunk (struct sctp_chunk*,int,TYPE_2__*) ; 
 struct sctp_chunk* sctp_make_chunk (struct sctp_association const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

struct sctp_chunk *sctp_make_cwr(const struct sctp_association *asoc,
			    const __u32 lowest_tsn,
			    const struct sctp_chunk *chunk)
{
	struct sctp_chunk *retval;
	sctp_cwrhdr_t cwr;

	cwr.lowest_tsn = htonl(lowest_tsn);
	retval = sctp_make_chunk(asoc, SCTP_CID_ECN_CWR, 0,
				 sizeof(sctp_cwrhdr_t));

	if (!retval)
		goto nodata;

	retval->subh.ecn_cwr_hdr =
		sctp_addto_chunk(retval, sizeof(cwr), &cwr);

	/* RFC 2960 6.4 Multi-homed SCTP Endpoints
	 *
	 * An endpoint SHOULD transmit reply chunks (e.g., SACK,
	 * HEARTBEAT ACK, * etc.) to the same destination transport
	 * address from which it * received the DATA or control chunk
	 * to which it is replying.
	 *
	 * [Report a reduced congestion window back to where the ECNE
	 * came from.]
	 */
	if (chunk)
		retval->transport = chunk->transport;

nodata:
	return retval;
}
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
struct sctp_transport {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hbs_hdr; } ;
struct sctp_chunk {TYPE_1__ subh; struct sctp_transport* transport; } ;
struct sctp_association {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_CID_HEARTBEAT ; 
 int /*<<< orphan*/  sctp_addto_chunk (struct sctp_chunk*,size_t const,void const*) ; 
 struct sctp_chunk* sctp_make_chunk (struct sctp_association const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t const) ; 

struct sctp_chunk *sctp_make_heartbeat(const struct sctp_association *asoc,
				  const struct sctp_transport *transport,
				  const void *payload, const size_t paylen)
{
	struct sctp_chunk *retval = sctp_make_chunk(asoc, SCTP_CID_HEARTBEAT,
						    0, paylen);

	if (!retval)
		goto nodata;

	/* Cast away the 'const', as this is just telling the chunk
	 * what transport it belongs to.
	 */
	retval->transport = (struct sctp_transport *) transport;
	retval->subh.hbs_hdr = sctp_addto_chunk(retval, paylen, payload);

nodata:
	return retval;
}
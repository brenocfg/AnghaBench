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
struct sctp_packet {scalar_t__ has_auth; TYPE_1__* transport; } ;
struct sctp_chunk {int /*<<< orphan*/  auth; TYPE_2__* chunk_hdr; } ;
struct sctp_association {int dummy; } ;
typedef  int /*<<< orphan*/  sctp_xmit_t ;
struct TYPE_4__ {scalar_t__ type; } ;
struct TYPE_3__ {struct sctp_association* asoc; } ;

/* Variables and functions */
 scalar_t__ SCTP_CID_AUTH ; 
 int /*<<< orphan*/  SCTP_XMIT_OK ; 
 struct sctp_chunk* sctp_make_auth (struct sctp_association*) ; 
 int /*<<< orphan*/  sctp_packet_append_chunk (struct sctp_packet*,struct sctp_chunk*) ; 

__attribute__((used)) static sctp_xmit_t sctp_packet_bundle_auth(struct sctp_packet *pkt,
					   struct sctp_chunk *chunk)
{
	struct sctp_association *asoc = pkt->transport->asoc;
	struct sctp_chunk *auth;
	sctp_xmit_t retval = SCTP_XMIT_OK;

	/* if we don't have an association, we can't do authentication */
	if (!asoc)
		return retval;

	/* See if this is an auth chunk we are bundling or if
	 * auth is already bundled.
	 */
	if (chunk->chunk_hdr->type == SCTP_CID_AUTH || pkt->has_auth)
		return retval;

	/* if the peer did not request this chunk to be authenticated,
	 * don't do it
	 */
	if (!chunk->auth)
		return retval;

	auth = sctp_make_auth(asoc);
	if (!auth)
		return retval;

	retval = sctp_packet_append_chunk(pkt, auth);

	return retval;
}
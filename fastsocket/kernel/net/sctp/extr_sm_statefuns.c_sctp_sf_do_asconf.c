#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  length; } ;
union sctp_addr_param {TYPE_2__ p; } ;
struct sctp_paramhdr {int dummy; } ;
struct sctp_endpoint {int dummy; } ;
struct sctp_chunk {int /*<<< orphan*/  source; int /*<<< orphan*/  dest; int /*<<< orphan*/ * transport; int /*<<< orphan*/  has_asconf; scalar_t__ chunk_end; TYPE_1__* skb; int /*<<< orphan*/  auth; } ;
struct TYPE_7__ {scalar_t__ addip_serial; } ;
struct sctp_association {TYPE_3__ peer; } ;
typedef  int /*<<< orphan*/  sctp_subtype_t ;
typedef  int /*<<< orphan*/  sctp_paramhdr_t ;
typedef  int /*<<< orphan*/  sctp_disposition_t ;
typedef  int /*<<< orphan*/  sctp_cmd_seq_t ;
struct TYPE_8__ {int /*<<< orphan*/  serial; scalar_t__ params; } ;
typedef  TYPE_4__ sctp_addiphdr_t ;
typedef  int /*<<< orphan*/  sctp_addip_chunk_t ;
typedef  scalar_t__ __u32 ;
struct TYPE_5__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_CHUNK (struct sctp_chunk*) ; 
 int /*<<< orphan*/  SCTP_CMD_REPLY ; 
 int /*<<< orphan*/  SCTP_CMD_REPORT_BAD_TAG ; 
 int /*<<< orphan*/  SCTP_DISPOSITION_CONSUME ; 
 int /*<<< orphan*/  SCTP_DISPOSITION_DISCARD ; 
 int /*<<< orphan*/  SCTP_DISPOSITION_NOMEM ; 
 int /*<<< orphan*/  SCTP_NULL () ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_add_cmd_sf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_addip_noauth ; 
 int /*<<< orphan*/  sctp_assoc_clean_asconf_ack_cache (struct sctp_association const*) ; 
 struct sctp_chunk* sctp_assoc_lookup_asconf_ack (struct sctp_association const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_chunk_length_valid (struct sctp_chunk*,int) ; 
 struct sctp_chunk* sctp_process_asconf (struct sctp_association*,struct sctp_chunk*) ; 
 int /*<<< orphan*/  sctp_sf_discard_chunk (struct sctp_endpoint const*,struct sctp_association const*,int /*<<< orphan*/  const,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_sf_pdiscard (struct sctp_endpoint const*,struct sctp_association const*,int /*<<< orphan*/  const,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_sf_violation_chunklen (struct sctp_endpoint const*,struct sctp_association const*,int /*<<< orphan*/  const,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_sf_violation_paramlen (struct sctp_endpoint const*,struct sctp_association const*,int /*<<< orphan*/  const,void*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_verify_asconf (struct sctp_association const*,int /*<<< orphan*/ *,void*,struct sctp_paramhdr**) ; 
 int /*<<< orphan*/  sctp_vtag_verify (struct sctp_chunk*,struct sctp_association const*) ; 

sctp_disposition_t sctp_sf_do_asconf(const struct sctp_endpoint *ep,
				     const struct sctp_association *asoc,
				     const sctp_subtype_t type, void *arg,
				     sctp_cmd_seq_t *commands)
{
	struct sctp_chunk	*chunk = arg;
	struct sctp_chunk	*asconf_ack = NULL;
	struct sctp_paramhdr	*err_param = NULL;
	sctp_addiphdr_t		*hdr;
	union sctp_addr_param	*addr_param;
	__u32			serial;
	int			length;

	if (!sctp_vtag_verify(chunk, asoc)) {
		sctp_add_cmd_sf(commands, SCTP_CMD_REPORT_BAD_TAG,
				SCTP_NULL());
		return sctp_sf_pdiscard(ep, asoc, type, arg, commands);
	}

	/* ADD-IP: Section 4.1.1
	 * This chunk MUST be sent in an authenticated way by using
	 * the mechanism defined in [I-D.ietf-tsvwg-sctp-auth]. If this chunk
	 * is received unauthenticated it MUST be silently discarded as
	 * described in [I-D.ietf-tsvwg-sctp-auth].
	 */
	if (!sctp_addip_noauth && !chunk->auth)
		return sctp_sf_discard_chunk(ep, asoc, type, arg, commands);

	/* Make sure that the ASCONF ADDIP chunk has a valid length.  */
	if (!sctp_chunk_length_valid(chunk, sizeof(sctp_addip_chunk_t)))
		return sctp_sf_violation_chunklen(ep, asoc, type, arg,
						  commands);

	hdr = (sctp_addiphdr_t *)chunk->skb->data;
	serial = ntohl(hdr->serial);

	addr_param = (union sctp_addr_param *)hdr->params;
	length = ntohs(addr_param->p.length);
	if (length < sizeof(sctp_paramhdr_t))
		return sctp_sf_violation_paramlen(ep, asoc, type, arg,
			   (void *)addr_param, commands);

	/* Verify the ASCONF chunk before processing it. */
	if (!sctp_verify_asconf(asoc,
			    (sctp_paramhdr_t *)((void *)addr_param + length),
			    (void *)chunk->chunk_end,
			    &err_param))
		return sctp_sf_violation_paramlen(ep, asoc, type, arg,
						  (void *)err_param, commands);

	/* ADDIP 5.2 E1) Compare the value of the serial number to the value
	 * the endpoint stored in a new association variable
	 * 'Peer-Serial-Number'.
	 */
	if (serial == asoc->peer.addip_serial + 1) {
		/* If this is the first instance of ASCONF in the packet,
		 * we can clean our old ASCONF-ACKs.
		 */
		if (!chunk->has_asconf)
			sctp_assoc_clean_asconf_ack_cache(asoc);

		/* ADDIP 5.2 E4) When the Sequence Number matches the next one
		 * expected, process the ASCONF as described below and after
		 * processing the ASCONF Chunk, append an ASCONF-ACK Chunk to
		 * the response packet and cache a copy of it (in the event it
		 * later needs to be retransmitted).
		 *
		 * Essentially, do V1-V5.
		 */
		asconf_ack = sctp_process_asconf((struct sctp_association *)
						 asoc, chunk);
		if (!asconf_ack)
			return SCTP_DISPOSITION_NOMEM;
	} else if (serial < asoc->peer.addip_serial + 1) {
		/* ADDIP 5.2 E2)
		 * If the value found in the Sequence Number is less than the
		 * ('Peer- Sequence-Number' + 1), simply skip to the next
		 * ASCONF, and include in the outbound response packet
		 * any previously cached ASCONF-ACK response that was
		 * sent and saved that matches the Sequence Number of the
		 * ASCONF.  Note: It is possible that no cached ASCONF-ACK
		 * Chunk exists.  This will occur when an older ASCONF
		 * arrives out of order.  In such a case, the receiver
		 * should skip the ASCONF Chunk and not include ASCONF-ACK
		 * Chunk for that chunk.
		 */
		asconf_ack = sctp_assoc_lookup_asconf_ack(asoc, hdr->serial);
		if (!asconf_ack)
			return SCTP_DISPOSITION_DISCARD;

		/* Reset the transport so that we select the correct one
		 * this time around.  This is to make sure that we don't
		 * accidentally use a stale transport that's been removed.
		 */
		asconf_ack->transport = NULL;
	} else {
		/* ADDIP 5.2 E5) Otherwise, the ASCONF Chunk is discarded since
		 * it must be either a stale packet or from an attacker.
		 */
		return SCTP_DISPOSITION_DISCARD;
	}

	/* ADDIP 5.2 E6)  The destination address of the SCTP packet
	 * containing the ASCONF-ACK Chunks MUST be the source address of
	 * the SCTP packet that held the ASCONF Chunks.
	 *
	 * To do this properly, we'll set the destination address of the chunk
	 * and at the transmit time, will try look up the transport to use.
	 * Since ASCONFs may be bundled, the correct transport may not be
	 * created untill we process the entire packet, thus this workaround.
	 */
	asconf_ack->dest = chunk->source;
	sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(asconf_ack));

	return SCTP_DISPOSITION_CONSUME;
}
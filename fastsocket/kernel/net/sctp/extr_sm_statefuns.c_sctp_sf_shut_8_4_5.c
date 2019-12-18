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
struct sctp_packet {int /*<<< orphan*/  vtag; } ;
struct TYPE_6__ {int /*<<< orphan*/  sk; } ;
struct sctp_endpoint {TYPE_3__ base; } ;
struct sctp_chunk {TYPE_2__* skb; TYPE_1__* sctp_hdr; } ;
struct sctp_association {int dummy; } ;
typedef  int /*<<< orphan*/  sctp_subtype_t ;
typedef  int /*<<< orphan*/  sctp_disposition_t ;
typedef  int /*<<< orphan*/  sctp_cmd_seq_t ;
typedef  int /*<<< orphan*/  sctp_chunkhdr_t ;
struct TYPE_5__ {int /*<<< orphan*/  sk; } ;
struct TYPE_4__ {int /*<<< orphan*/  vtag; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_CMD_SEND_PKT ; 
 int /*<<< orphan*/  SCTP_DISPOSITION_NOMEM ; 
 int /*<<< orphan*/  SCTP_INC_STATS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_MIB_OUTCTRLCHUNKS ; 
 int /*<<< orphan*/  SCTP_PACKET (struct sctp_packet*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_add_cmd_sf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_chunk_length_valid (struct sctp_chunk*,int) ; 
 struct sctp_chunk* sctp_make_shutdown_complete (struct sctp_association const*,struct sctp_chunk*) ; 
 int /*<<< orphan*/  sctp_ootb_pkt_free (struct sctp_packet*) ; 
 struct sctp_packet* sctp_ootb_pkt_new (struct sctp_association const*,struct sctp_chunk*) ; 
 int /*<<< orphan*/  sctp_packet_append_chunk (struct sctp_packet*,struct sctp_chunk*) ; 
 int /*<<< orphan*/  sctp_sf_pdiscard (struct sctp_endpoint const*,struct sctp_association const*,int /*<<< orphan*/  const,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ sctp_test_T_bit (struct sctp_chunk*) ; 

__attribute__((used)) static sctp_disposition_t sctp_sf_shut_8_4_5(const struct sctp_endpoint *ep,
					     const struct sctp_association *asoc,
					     const sctp_subtype_t type,
					     void *arg,
					     sctp_cmd_seq_t *commands)
{
	struct sctp_packet *packet = NULL;
	struct sctp_chunk *chunk = arg;
	struct sctp_chunk *shut;

	packet = sctp_ootb_pkt_new(asoc, chunk);

	if (packet) {
		/* Make an SHUTDOWN_COMPLETE.
		 * The T bit will be set if the asoc is NULL.
		 */
		shut = sctp_make_shutdown_complete(asoc, chunk);
		if (!shut) {
			sctp_ootb_pkt_free(packet);
			return SCTP_DISPOSITION_NOMEM;
		}

		/* Reflect vtag if T-Bit is set */
		if (sctp_test_T_bit(shut))
			packet->vtag = ntohl(chunk->sctp_hdr->vtag);

		/* Set the skb to the belonging sock for accounting.  */
		shut->skb->sk = ep->base.sk;

		sctp_packet_append_chunk(packet, shut);

		sctp_add_cmd_sf(commands, SCTP_CMD_SEND_PKT,
				SCTP_PACKET(packet));

		SCTP_INC_STATS(SCTP_MIB_OUTCTRLCHUNKS);

		/* If the chunk length is invalid, we don't want to process
		 * the reset of the packet.
		 */
		if (!sctp_chunk_length_valid(chunk, sizeof(sctp_chunkhdr_t)))
			return sctp_sf_pdiscard(ep, asoc, type, arg, commands);

		/* We need to discard the rest of the packet to prevent
		 * potential bomming attacks from additional bundled chunks.
		 * This is documented in SCTP Threats ID.
		 */
		return sctp_sf_pdiscard(ep, asoc, type, arg, commands);
	}

	return SCTP_DISPOSITION_NOMEM;
}
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
struct sctp_endpoint {int dummy; } ;
struct sctp_chunk {int /*<<< orphan*/  dest; } ;
struct TYPE_2__ {int /*<<< orphan*/  bind_addr; } ;
struct sctp_association {TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  sctp_subtype_t ;
typedef  int /*<<< orphan*/  sctp_disposition_t ;
typedef  int /*<<< orphan*/  sctp_cmd_seq_t ;
typedef  int /*<<< orphan*/  sctp_abort_chunk_t ;

/* Variables and functions */
 scalar_t__ SCTP_ADDR_DEL ; 
 int /*<<< orphan*/  __sctp_sf_do_9_1_abort (struct sctp_endpoint const*,struct sctp_association const*,int /*<<< orphan*/  const,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ sctp_bind_addr_state (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_chunk_length_valid (struct sctp_chunk*,int) ; 
 int /*<<< orphan*/  sctp_sf_discard_chunk (struct sctp_endpoint const*,struct sctp_association const*,int /*<<< orphan*/  const,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_sf_pdiscard (struct sctp_endpoint const*,struct sctp_association const*,int /*<<< orphan*/  const,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_vtag_verify_either (struct sctp_chunk*,struct sctp_association const*) ; 

sctp_disposition_t sctp_sf_shutdown_pending_abort(
	const struct sctp_endpoint *ep,
	const struct sctp_association *asoc,
	const sctp_subtype_t type,
	void *arg,
	sctp_cmd_seq_t *commands)
{
	struct sctp_chunk *chunk = arg;

	if (!sctp_vtag_verify_either(chunk, asoc))
		return sctp_sf_pdiscard(ep, asoc, type, arg, commands);

	/* Make sure that the ABORT chunk has a valid length.
	 * Since this is an ABORT chunk, we have to discard it
	 * because of the following text:
	 * RFC 2960, Section 3.3.7
	 *    If an endpoint receives an ABORT with a format error or for an
	 *    association that doesn't exist, it MUST silently discard it.
	 * Becasue the length is "invalid", we can't really discard just
	 * as we do not know its true length.  So, to be safe, discard the
	 * packet.
	 */
	if (!sctp_chunk_length_valid(chunk, sizeof(sctp_abort_chunk_t)))
		return sctp_sf_pdiscard(ep, asoc, type, arg, commands);

	/* ADD-IP: Special case for ABORT chunks
	 * F4)  One special consideration is that ABORT Chunks arriving
	 * destined to the IP address being deleted MUST be
	 * ignored (see Section 5.3.1 for further details).
	 */
	if (SCTP_ADDR_DEL ==
		    sctp_bind_addr_state(&asoc->base.bind_addr, &chunk->dest))
		return sctp_sf_discard_chunk(ep, asoc, type, arg, commands);

	return __sctp_sf_do_9_1_abort(ep, asoc, type, arg, commands);
}
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
struct sctp_transport {int dummy; } ;
struct sctp_endpoint {int dummy; } ;
struct sctp_association {int dummy; } ;
typedef  int /*<<< orphan*/  sctp_subtype_t ;
typedef  scalar_t__ sctp_disposition_t ;
typedef  int /*<<< orphan*/  sctp_cmd_seq_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_CMD_TRANSPORT_HB_SENT ; 
 scalar_t__ SCTP_DISPOSITION_CONSUME ; 
 scalar_t__ SCTP_DISPOSITION_NOMEM ; 
 int /*<<< orphan*/  SCTP_TRANSPORT (void*) ; 
 int /*<<< orphan*/  sctp_add_cmd_sf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_sf_heartbeat (struct sctp_endpoint const*,struct sctp_association const*,int /*<<< orphan*/  const,struct sctp_transport*,int /*<<< orphan*/ *) ; 

sctp_disposition_t sctp_sf_do_prm_requestheartbeat(
					const struct sctp_endpoint *ep,
					const struct sctp_association *asoc,
					const sctp_subtype_t type,
					void *arg,
					sctp_cmd_seq_t *commands)
{
	if (SCTP_DISPOSITION_NOMEM == sctp_sf_heartbeat(ep, asoc, type,
				      (struct sctp_transport *)arg, commands))
		return SCTP_DISPOSITION_NOMEM;

	/*
	 * RFC 2960 (bis), section 8.3
	 *
	 *    D) Request an on-demand HEARTBEAT on a specific destination
	 *    transport address of a given association.
	 *
	 *    The endpoint should increment the respective error  counter of
	 *    the destination transport address each time a HEARTBEAT is sent
	 *    to that address and not acknowledged within one RTO.
	 *
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_TRANSPORT_HB_SENT,
			SCTP_TRANSPORT(arg));
	return SCTP_DISPOSITION_CONSUME;
}
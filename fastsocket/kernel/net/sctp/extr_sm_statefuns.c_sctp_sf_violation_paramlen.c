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
struct sctp_paramhdr {int dummy; } ;
struct sctp_endpoint {int dummy; } ;
struct sctp_chunk {int dummy; } ;
struct sctp_association {int dummy; } ;
typedef  int /*<<< orphan*/  sctp_subtype_t ;
typedef  int /*<<< orphan*/  sctp_disposition_t ;
typedef  int /*<<< orphan*/  sctp_cmd_seq_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECONNABORTED ; 
 int /*<<< orphan*/  SCTP_CHUNK (struct sctp_chunk*) ; 
 int /*<<< orphan*/  SCTP_CID_ABORT ; 
 int /*<<< orphan*/  SCTP_CMD_ASSOC_FAILED ; 
 int /*<<< orphan*/  SCTP_CMD_REPLY ; 
 int /*<<< orphan*/  SCTP_CMD_SET_SK_ERR ; 
 int /*<<< orphan*/  SCTP_DEC_STATS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_DISPOSITION_ABORT ; 
 int /*<<< orphan*/  SCTP_DISPOSITION_NOMEM ; 
 int /*<<< orphan*/  SCTP_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_ERROR_PROTO_VIOLATION ; 
 int /*<<< orphan*/  SCTP_INC_STATS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_MIB_ABORTEDS ; 
 int /*<<< orphan*/  SCTP_MIB_CURRESTAB ; 
 int /*<<< orphan*/  SCTP_MIB_OUTCTRLCHUNKS ; 
 int /*<<< orphan*/  SCTP_PERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_ST_CHUNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_add_cmd_sf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_auth_recv_cid (int /*<<< orphan*/ ,struct sctp_association const*) ; 
 struct sctp_chunk* sctp_make_violation_paramlen (struct sctp_association const*,struct sctp_chunk*,struct sctp_paramhdr*) ; 
 int /*<<< orphan*/  sctp_sf_pdiscard (struct sctp_endpoint const*,struct sctp_association const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static sctp_disposition_t sctp_sf_violation_paramlen(
				     const struct sctp_endpoint *ep,
				     const struct sctp_association *asoc,
				     const sctp_subtype_t type,
				     void *arg, void *ext,
				     sctp_cmd_seq_t *commands)
{
	struct sctp_chunk *chunk =  arg;
	struct sctp_paramhdr *param = ext;
	struct sctp_chunk *abort = NULL;

	if (sctp_auth_recv_cid(SCTP_CID_ABORT, asoc))
		goto discard;

	/* Make the abort chunk. */
	abort = sctp_make_violation_paramlen(asoc, chunk, param);
	if (!abort)
		goto nomem;

	sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(abort));
	SCTP_INC_STATS(SCTP_MIB_OUTCTRLCHUNKS);

	sctp_add_cmd_sf(commands, SCTP_CMD_SET_SK_ERR,
			SCTP_ERROR(ECONNABORTED));
	sctp_add_cmd_sf(commands, SCTP_CMD_ASSOC_FAILED,
			SCTP_PERR(SCTP_ERROR_PROTO_VIOLATION));
	SCTP_DEC_STATS(SCTP_MIB_CURRESTAB);
	SCTP_INC_STATS(SCTP_MIB_ABORTEDS);

discard:
	sctp_sf_pdiscard(ep, asoc, SCTP_ST_CHUNK(0), arg, commands);
	return SCTP_DISPOSITION_ABORT;
nomem:
	return SCTP_DISPOSITION_NOMEM;
}
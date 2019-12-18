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
struct sctp_paramhdr {int /*<<< orphan*/  length; int /*<<< orphan*/  type; } ;
struct sctp_chunk {TYPE_1__* chunk_hdr; } ;
struct sctp_association {int dummy; } ;
typedef  int /*<<< orphan*/  sctp_paramhdr_t ;
typedef  int /*<<< orphan*/  sctp_errhdr_t ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_2__ {int /*<<< orphan*/  length; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_ERROR_PROTO_VIOLATION ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_addto_chunk (struct sctp_chunk*,size_t const,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  sctp_addto_param (struct sctp_chunk*,int,struct sctp_paramhdr*) ; 
 int /*<<< orphan*/  sctp_init_cause (struct sctp_chunk*,int /*<<< orphan*/ ,size_t const) ; 
 struct sctp_chunk* sctp_make_abort (struct sctp_association const*,struct sctp_chunk const*,int) ; 

struct sctp_chunk *sctp_make_abort_violation(
	const struct sctp_association *asoc,
	const struct sctp_chunk *chunk,
	const __u8   *payload,
	const size_t paylen)
{
	struct sctp_chunk  *retval;
	struct sctp_paramhdr phdr;

	retval = sctp_make_abort(asoc, chunk, sizeof(sctp_errhdr_t) + paylen
					+ sizeof(sctp_paramhdr_t));
	if (!retval)
		goto end;

	sctp_init_cause(retval, SCTP_ERROR_PROTO_VIOLATION, paylen
					+ sizeof(sctp_paramhdr_t));

	phdr.type = htons(chunk->chunk_hdr->type);
	phdr.length = chunk->chunk_hdr->length;
	sctp_addto_chunk(retval, paylen, payload);
	sctp_addto_param(retval, sizeof(sctp_paramhdr_t), &phdr);

end:
	return retval;
}
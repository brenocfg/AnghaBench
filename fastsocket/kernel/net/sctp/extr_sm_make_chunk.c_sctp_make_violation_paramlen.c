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
struct sctp_chunk {int dummy; } ;
struct sctp_association {int dummy; } ;
typedef  int /*<<< orphan*/  sctp_paramhdr_t ;
typedef  int /*<<< orphan*/  sctp_errhdr_t ;
typedef  int /*<<< orphan*/  error ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_ERROR_PROTO_VIOLATION ; 
 int /*<<< orphan*/  sctp_addto_chunk (struct sctp_chunk*,int,char const*) ; 
 int /*<<< orphan*/  sctp_addto_param (struct sctp_chunk*,int,struct sctp_paramhdr*) ; 
 int /*<<< orphan*/  sctp_init_cause (struct sctp_chunk*,int /*<<< orphan*/ ,int) ; 
 struct sctp_chunk* sctp_make_abort (struct sctp_association const*,struct sctp_chunk const*,size_t) ; 

struct sctp_chunk *sctp_make_violation_paramlen(
	const struct sctp_association *asoc,
	const struct sctp_chunk *chunk,
	struct sctp_paramhdr *param)
{
	struct sctp_chunk *retval;
	static const char error[] = "The following parameter had invalid length:";
	size_t payload_len = sizeof(error) + sizeof(sctp_errhdr_t) +
				sizeof(sctp_paramhdr_t);

	retval = sctp_make_abort(asoc, chunk, payload_len);
	if (!retval)
		goto nodata;

	sctp_init_cause(retval, SCTP_ERROR_PROTO_VIOLATION,
			sizeof(error) + sizeof(sctp_paramhdr_t));
	sctp_addto_chunk(retval, sizeof(error), error);
	sctp_addto_param(retval, sizeof(sctp_paramhdr_t), param);

nodata:
	return retval;
}
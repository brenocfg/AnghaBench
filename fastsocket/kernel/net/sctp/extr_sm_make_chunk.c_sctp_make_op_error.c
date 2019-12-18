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
struct sctp_chunk {int dummy; } ;
struct sctp_association {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  sctp_addto_chunk (struct sctp_chunk*,size_t,void const*) ; 
 int /*<<< orphan*/  sctp_addto_param (struct sctp_chunk*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_init_cause (struct sctp_chunk*,int /*<<< orphan*/ ,size_t) ; 
 struct sctp_chunk* sctp_make_op_error_space (struct sctp_association const*,struct sctp_chunk const*,size_t) ; 

struct sctp_chunk *sctp_make_op_error(const struct sctp_association *asoc,
				 const struct sctp_chunk *chunk,
				 __be16 cause_code, const void *payload,
				 size_t paylen, size_t reserve_tail)
{
	struct sctp_chunk *retval;

	retval = sctp_make_op_error_space(asoc, chunk, paylen + reserve_tail);
	if (!retval)
		goto nodata;

	sctp_init_cause(retval, cause_code, paylen + reserve_tail);
	sctp_addto_chunk(retval, paylen, payload);
	if (reserve_tail)
		sctp_addto_param(retval, reserve_tail, NULL);

nodata:
	return retval;
}
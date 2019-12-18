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
struct sctp_endpoint {int dummy; } ;
struct sctp_association {int dummy; } ;
typedef  int /*<<< orphan*/  sctp_subtype_t ;
typedef  int /*<<< orphan*/  sctp_disposition_t ;
typedef  int /*<<< orphan*/  sctp_cmd_seq_t ;
typedef  int /*<<< orphan*/  err_str ;

/* Variables and functions */
 int /*<<< orphan*/  sctp_sf_abort_violation (struct sctp_endpoint const*,struct sctp_association const*,void*,int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  sctp_sf_violation (struct sctp_endpoint const*,struct sctp_association const*,int /*<<< orphan*/  const,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static sctp_disposition_t sctp_sf_violation_chunk(
				     const struct sctp_endpoint *ep,
				     const struct sctp_association *asoc,
				     const sctp_subtype_t type,
				     void *arg,
				     sctp_cmd_seq_t *commands)
{
	static const char err_str[]="The following chunk violates protocol:";

	if (!asoc)
		return sctp_sf_violation(ep, asoc, type, arg, commands);

	return sctp_sf_abort_violation(ep, asoc, arg, commands, err_str,
					sizeof(err_str));
}
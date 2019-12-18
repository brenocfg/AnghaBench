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
struct TYPE_2__ {scalar_t__ length; } ;
struct sctp_chunks_param {int* chunks; TYPE_1__ param_hdr; } ;
typedef  int /*<<< orphan*/  sctp_paramhdr_t ;
typedef  int sctp_cid_t ;

/* Variables and functions */
#define  SCTP_CID_AUTH 131 
#define  SCTP_CID_INIT 130 
#define  SCTP_CID_INIT_ACK 129 
#define  SCTP_CID_SHUTDOWN_COMPLETE 128 
 int ntohs (scalar_t__) ; 

__attribute__((used)) static int __sctp_auth_cid(sctp_cid_t chunk, struct sctp_chunks_param *param)
{
	unsigned short len;
	int found = 0;
	int i;

	if (!param || param->param_hdr.length == 0)
		return 0;

	len = ntohs(param->param_hdr.length) - sizeof(sctp_paramhdr_t);

	/* SCTP-AUTH, Section 3.2
	 *    The chunk types for INIT, INIT-ACK, SHUTDOWN-COMPLETE and AUTH
	 *    chunks MUST NOT be listed in the CHUNKS parameter.  However, if
	 *    a CHUNKS parameter is received then the types for INIT, INIT-ACK,
	 *    SHUTDOWN-COMPLETE and AUTH chunks MUST be ignored.
	 */
	for (i = 0; !found && i < len; i++) {
		switch (param->chunks[i]) {
		    case SCTP_CID_INIT:
		    case SCTP_CID_INIT_ACK:
		    case SCTP_CID_SHUTDOWN_COMPLETE:
		    case SCTP_CID_AUTH:
			break;

		    default:
			if (param->chunks[i] == chunk)
			    found = 1;
			break;
		}
	}

	return found;
}
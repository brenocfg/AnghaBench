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
union sctp_params {TYPE_3__* ext; TYPE_2__* p; } ;
struct TYPE_4__ {int prsctp_capable; int auth_capable; int asconf_capable; } ;
struct sctp_association {TYPE_1__ peer; } ;
typedef  int /*<<< orphan*/  sctp_paramhdr_t ;
typedef  int __u16 ;
struct TYPE_6__ {int* chunks; } ;
struct TYPE_5__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
#define  SCTP_CID_ASCONF 131 
#define  SCTP_CID_ASCONF_ACK 130 
#define  SCTP_CID_AUTH 129 
#define  SCTP_CID_FWD_TSN 128 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_addip_enable ; 
 int /*<<< orphan*/  sctp_auth_enable ; 
 int /*<<< orphan*/  sctp_prsctp_enable ; 

__attribute__((used)) static void sctp_process_ext_param(struct sctp_association *asoc,
				    union sctp_params param)
{
	__u16 num_ext = ntohs(param.p->length) - sizeof(sctp_paramhdr_t);
	int i;

	for (i = 0; i < num_ext; i++) {
		switch (param.ext->chunks[i]) {
		    case SCTP_CID_FWD_TSN:
			    if (sctp_prsctp_enable &&
				!asoc->peer.prsctp_capable)
				    asoc->peer.prsctp_capable = 1;
			    break;
		    case SCTP_CID_AUTH:
			    /* if the peer reports AUTH, assume that he
			     * supports AUTH.
			     */
			    if (sctp_auth_enable)
				    asoc->peer.auth_capable = 1;
			    break;
		    case SCTP_CID_ASCONF:
		    case SCTP_CID_ASCONF_ACK:
			    if (sctp_addip_enable)
				    asoc->peer.asconf_capable = 1;
			    break;
		    default:
			    break;
		}
	}
}
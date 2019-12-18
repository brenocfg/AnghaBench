#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
union sctp_params {TYPE_2__* ext; TYPE_1__* p; } ;
typedef  int /*<<< orphan*/  sctp_paramhdr_t ;
typedef  int __u16 ;
struct TYPE_4__ {int* chunks; } ;
struct TYPE_3__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
#define  SCTP_CID_ASCONF 130 
#define  SCTP_CID_ASCONF_ACK 129 
#define  SCTP_CID_AUTH 128 
 int ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_addip_enable ; 
 scalar_t__ sctp_addip_noauth ; 

__attribute__((used)) static int sctp_verify_ext_param(union sctp_params param)
{
	__u16 num_ext = ntohs(param.p->length) - sizeof(sctp_paramhdr_t);
	int have_auth = 0;
	int have_asconf = 0;
	int i;

	for (i = 0; i < num_ext; i++) {
		switch (param.ext->chunks[i]) {
		    case SCTP_CID_AUTH:
			    have_auth = 1;
			    break;
		    case SCTP_CID_ASCONF:
		    case SCTP_CID_ASCONF_ACK:
			    have_asconf = 1;
			    break;
		}
	}

	/* ADD-IP Security: The draft requires us to ABORT or ignore the
	 * INIT/INIT-ACK if ADD-IP is listed, but AUTH is not.  Do this
	 * only if ADD-IP is turned on and we are not backward-compatible
	 * mode.
	 */
	if (sctp_addip_noauth)
		return 1;

	if (sctp_addip_enable && !have_auth && have_asconf)
		return 0;

	return 1;
}
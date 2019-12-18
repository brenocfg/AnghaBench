#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t chunk; } ;
typedef  TYPE_1__ sctp_subtype_t ;

/* Variables and functions */
#define  SCTP_CID_ASCONF 131 
#define  SCTP_CID_ASCONF_ACK 130 
#define  SCTP_CID_AUTH 129 
 size_t SCTP_CID_BASE_MAX ; 
#define  SCTP_CID_FWD_TSN 128 
 char const** sctp_cid_tbl ; 

const char *sctp_cname(const sctp_subtype_t cid)
{
	if (cid.chunk <= SCTP_CID_BASE_MAX)
		return sctp_cid_tbl[cid.chunk];

	switch (cid.chunk) {
	case SCTP_CID_ASCONF:
		return "ASCONF";

	case SCTP_CID_ASCONF_ACK:
		return "ASCONF_ACK";

	case SCTP_CID_FWD_TSN:
		return "FWD_TSN";

	case SCTP_CID_AUTH:
		return "AUTH";

	default:
		break;
	}

	return "unknown chunk";
}
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
union sctp_params {void* v; struct sctp_paramhdr* p; } ;
struct sctp_paramhdr {int type; int /*<<< orphan*/  length; } ;
struct sctp_association {int dummy; } ;
typedef  void sctp_paramhdr_t ;
struct TYPE_3__ {int /*<<< orphan*/  length; } ;
struct TYPE_4__ {TYPE_1__ param_hdr; } ;
typedef  TYPE_2__ sctp_addip_param_t ;

/* Variables and functions */
#define  SCTP_PARAM_ADAPTATION_LAYER_IND 132 
#define  SCTP_PARAM_ADD_IP 131 
#define  SCTP_PARAM_DEL_IP 130 
#define  SCTP_PARAM_SET_PRIMARY 129 
#define  SCTP_PARAM_SUCCESS_REPORT 128 
 int /*<<< orphan*/  WORD_ROUND (int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

int sctp_verify_asconf(const struct sctp_association *asoc,
		       struct sctp_paramhdr *param_hdr, void *chunk_end,
		       struct sctp_paramhdr **errp) {
	sctp_addip_param_t *asconf_param;
	union sctp_params param;
	int length, plen;

	param.v = (sctp_paramhdr_t *) param_hdr;
	while (param.v <= chunk_end - sizeof(sctp_paramhdr_t)) {
		length = ntohs(param.p->length);
		*errp = param.p;

		if (param.v > chunk_end - length ||
		    length < sizeof(sctp_paramhdr_t))
			return 0;

		switch (param.p->type) {
		case SCTP_PARAM_ADD_IP:
		case SCTP_PARAM_DEL_IP:
		case SCTP_PARAM_SET_PRIMARY:
			asconf_param = (sctp_addip_param_t *)param.v;
			plen = ntohs(asconf_param->param_hdr.length);
			if (plen < sizeof(sctp_addip_param_t) +
			    sizeof(sctp_paramhdr_t))
				return 0;
			break;
		case SCTP_PARAM_SUCCESS_REPORT:
		case SCTP_PARAM_ADAPTATION_LAYER_IND:
			if (length != sizeof(sctp_addip_param_t))
				return 0;

			break;
		default:
			break;
		}

		param.v += WORD_ROUND(length);
	}

	if (param.v != chunk_end)
		return 0;

	return 1;
}
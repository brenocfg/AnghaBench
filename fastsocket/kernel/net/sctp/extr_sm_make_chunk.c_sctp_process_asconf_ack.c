#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  length; } ;
struct TYPE_10__ {TYPE_1__ param_hdr; } ;
union sctp_addr_param {TYPE_2__ v4; } ;
struct sctp_chunk {int /*<<< orphan*/  transmitted_list; TYPE_3__* skb; } ;
struct TYPE_12__ {int /*<<< orphan*/  addip_disabled_mask; } ;
struct sctp_association {struct sctp_chunk* addip_last_asconf; TYPE_4__ peer; } ;
typedef  int /*<<< orphan*/  sctp_addiphdr_t ;
struct TYPE_13__ {int /*<<< orphan*/  length; int /*<<< orphan*/  type; } ;
struct TYPE_14__ {TYPE_5__ param_hdr; } ;
typedef  TYPE_6__ sctp_addip_param_t ;
typedef  int /*<<< orphan*/  sctp_addip_chunk_t ;
typedef  int __be16 ;
struct TYPE_11__ {int len; scalar_t__ data; } ;

/* Variables and functions */
#define  SCTP_ERROR_DEL_LAST_IP 133 
#define  SCTP_ERROR_DEL_SRC_IP 132 
#define  SCTP_ERROR_NO_ERROR 131 
#define  SCTP_ERROR_REQ_REFUSED 130 
#define  SCTP_ERROR_RSRC_LOW 129 
#define  SCTP_ERROR_UNKNOWN_PARAM 128 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_asconf_param_success (struct sctp_association*,TYPE_6__*) ; 
 int /*<<< orphan*/  sctp_chunk_free (struct sctp_chunk*) ; 
 int sctp_get_asconf_response (struct sctp_chunk*,TYPE_6__*,int) ; 

int sctp_process_asconf_ack(struct sctp_association *asoc,
			    struct sctp_chunk *asconf_ack)
{
	struct sctp_chunk	*asconf = asoc->addip_last_asconf;
	union sctp_addr_param	*addr_param;
	sctp_addip_param_t	*asconf_param;
	int	length = 0;
	int	asconf_len = asconf->skb->len;
	int	all_param_pass = 0;
	int	no_err = 1;
	int	retval = 0;
	__be16	err_code = SCTP_ERROR_NO_ERROR;

	/* Skip the chunkhdr and addiphdr from the last asconf sent and store
	 * a pointer to address parameter.
	 */
	length = sizeof(sctp_addip_chunk_t);
	addr_param = (union sctp_addr_param *)(asconf->skb->data + length);
	asconf_len -= length;

	/* Skip the address parameter in the last asconf sent and store a
	 * pointer to the first asconf parameter.
	 */
	length = ntohs(addr_param->v4.param_hdr.length);
	asconf_param = (sctp_addip_param_t *)((void *)addr_param + length);
	asconf_len -= length;

	/* ADDIP 4.1
	 * A8) If there is no response(s) to specific TLV parameter(s), and no
	 * failures are indicated, then all request(s) are considered
	 * successful.
	 */
	if (asconf_ack->skb->len == sizeof(sctp_addiphdr_t))
		all_param_pass = 1;

	/* Process the TLVs contained in the last sent ASCONF chunk. */
	while (asconf_len > 0) {
		if (all_param_pass)
			err_code = SCTP_ERROR_NO_ERROR;
		else {
			err_code = sctp_get_asconf_response(asconf_ack,
							    asconf_param,
							    no_err);
			if (no_err && (SCTP_ERROR_NO_ERROR != err_code))
				no_err = 0;
		}

		switch (err_code) {
		case SCTP_ERROR_NO_ERROR:
			sctp_asconf_param_success(asoc, asconf_param);
			break;

		case SCTP_ERROR_RSRC_LOW:
			retval = 1;
			break;

		case SCTP_ERROR_UNKNOWN_PARAM:
			/* Disable sending this type of asconf parameter in
			 * future.
			 */
			asoc->peer.addip_disabled_mask |=
				asconf_param->param_hdr.type;
			break;

		case SCTP_ERROR_REQ_REFUSED:
		case SCTP_ERROR_DEL_LAST_IP:
		case SCTP_ERROR_DEL_SRC_IP:
		default:
			 break;
		}

		/* Skip the processed asconf parameter and move to the next
		 * one.
		 */
		length = ntohs(asconf_param->param_hdr.length);
		asconf_param = (sctp_addip_param_t *)((void *)asconf_param +
						      length);
		asconf_len -= length;
	}

	/* Free the cached last sent asconf chunk. */
	list_del_init(&asconf->transmitted_list);
	sctp_chunk_free(asconf);
	asoc->addip_last_asconf = NULL;

	return retval;
}
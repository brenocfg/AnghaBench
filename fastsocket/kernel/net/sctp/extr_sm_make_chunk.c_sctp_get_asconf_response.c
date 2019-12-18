#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sctp_chunk {TYPE_2__* skb; TYPE_1__* chunk_hdr; } ;
struct TYPE_10__ {int /*<<< orphan*/  cause; } ;
typedef  TYPE_4__ sctp_errhdr_t ;
typedef  int /*<<< orphan*/  sctp_chunkhdr_t ;
typedef  int /*<<< orphan*/  sctp_addiphdr_t ;
struct TYPE_9__ {int type; int /*<<< orphan*/  length; } ;
struct TYPE_11__ {scalar_t__ crr_id; TYPE_3__ param_hdr; } ;
typedef  TYPE_5__ sctp_addip_param_t ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_8__ {scalar_t__ data; } ;
struct TYPE_7__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_ERROR_INV_PARAM ; 
 int /*<<< orphan*/  SCTP_ERROR_NO_ERROR ; 
 int /*<<< orphan*/  SCTP_ERROR_REQ_REFUSED ; 
#define  SCTP_PARAM_ERR_CAUSE 129 
#define  SCTP_PARAM_SUCCESS_REPORT 128 
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be16 sctp_get_asconf_response(struct sctp_chunk *asconf_ack,
				      sctp_addip_param_t *asconf_param,
				      int no_err)
{
	sctp_addip_param_t	*asconf_ack_param;
	sctp_errhdr_t		*err_param;
	int			length;
	int			asconf_ack_len;
	__be16			err_code;

	if (no_err)
		err_code = SCTP_ERROR_NO_ERROR;
	else
		err_code = SCTP_ERROR_REQ_REFUSED;

	asconf_ack_len = ntohs(asconf_ack->chunk_hdr->length) -
			     sizeof(sctp_chunkhdr_t);

	/* Skip the addiphdr from the asconf_ack chunk and store a pointer to
	 * the first asconf_ack parameter.
	 */
	length = sizeof(sctp_addiphdr_t);
	asconf_ack_param = (sctp_addip_param_t *)(asconf_ack->skb->data +
						  length);
	asconf_ack_len -= length;

	while (asconf_ack_len > 0) {
		if (asconf_ack_param->crr_id == asconf_param->crr_id) {
			switch(asconf_ack_param->param_hdr.type) {
			case SCTP_PARAM_SUCCESS_REPORT:
				return SCTP_ERROR_NO_ERROR;
			case SCTP_PARAM_ERR_CAUSE:
				length = sizeof(sctp_addip_param_t);
				err_param = (sctp_errhdr_t *)
					   ((void *)asconf_ack_param + length);
				asconf_ack_len -= length;
				if (asconf_ack_len > 0)
					return err_param->cause;
				else
					return SCTP_ERROR_INV_PARAM;
				break;
			default:
				return SCTP_ERROR_INV_PARAM;
			}
		}

		length = ntohs(asconf_ack_param->param_hdr.length);
		asconf_ack_param = (sctp_addip_param_t *)
					((void *)asconf_ack_param + length);
		asconf_ack_len -= length;
	}

	return err_code;
}
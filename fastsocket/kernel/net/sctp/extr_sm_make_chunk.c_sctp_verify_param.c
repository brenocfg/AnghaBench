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
union sctp_params {TYPE_1__* p; } ;
struct sctp_hmac_algo_param {int* hmac_ids; } ;
struct sctp_chunk {int dummy; } ;
struct sctp_association {int dummy; } ;
typedef  int /*<<< orphan*/  sctp_paramhdr_t ;
typedef  int sctp_ierror_t ;
typedef  int /*<<< orphan*/  sctp_cid_t ;
typedef  int __u16 ;
struct TYPE_2__ {int type; int length; } ;

/* Variables and functions */
 int SCTP_AUTH_HMAC_ID_SHA1 ; 
 int /*<<< orphan*/  SCTP_AUTH_RANDOM_LENGTH ; 
 int /*<<< orphan*/  SCTP_DEBUG_PRINTK (char*,int,int /*<<< orphan*/ ) ; 
 int SCTP_IERROR_ABORT ; 
 int SCTP_IERROR_NO_ERROR ; 
#define  SCTP_PARAM_ADAPTATION_LAYER_IND 143 
#define  SCTP_PARAM_CHUNKS 142 
#define  SCTP_PARAM_COOKIE_PRESERVATIVE 141 
#define  SCTP_PARAM_ECN_CAPABLE 140 
#define  SCTP_PARAM_FWD_TSN_SUPPORT 139 
#define  SCTP_PARAM_HEARTBEAT_INFO 138 
#define  SCTP_PARAM_HMAC_ALGO 137 
#define  SCTP_PARAM_HOST_NAME_ADDRESS 136 
#define  SCTP_PARAM_IPV4_ADDRESS 135 
#define  SCTP_PARAM_IPV6_ADDRESS 134 
#define  SCTP_PARAM_RANDOM 133 
#define  SCTP_PARAM_SET_PRIMARY 132 
#define  SCTP_PARAM_STATE_COOKIE 131 
#define  SCTP_PARAM_SUPPORTED_ADDRESS_TYPES 130 
#define  SCTP_PARAM_SUPPORTED_EXT 129 
#define  SCTP_PARAM_UNRECOGNIZED_PARAMETERS 128 
 int ntohs (int) ; 
 int /*<<< orphan*/  sctp_addip_enable ; 
 int /*<<< orphan*/  sctp_auth_enable ; 
 int /*<<< orphan*/  sctp_process_hn_param (struct sctp_association const*,union sctp_params,struct sctp_chunk*,struct sctp_chunk**) ; 
 int /*<<< orphan*/  sctp_process_inv_paramlength (struct sctp_association const*,TYPE_1__*,struct sctp_chunk*,struct sctp_chunk**) ; 
 int sctp_process_unk_param (struct sctp_association const*,union sctp_params,struct sctp_chunk*,struct sctp_chunk**) ; 
 int /*<<< orphan*/  sctp_prsctp_enable ; 
 int /*<<< orphan*/  sctp_verify_ext_param (union sctp_params) ; 

__attribute__((used)) static sctp_ierror_t sctp_verify_param(const struct sctp_association *asoc,
					union sctp_params param,
					sctp_cid_t cid,
					struct sctp_chunk *chunk,
					struct sctp_chunk **err_chunk)
{
	struct sctp_hmac_algo_param *hmacs;
	int retval = SCTP_IERROR_NO_ERROR;
	__u16 n_elt, id = 0;
	int i;

	/* FIXME - This routine is not looking at each parameter per the
	 * chunk type, i.e., unrecognized parameters should be further
	 * identified based on the chunk id.
	 */

	switch (param.p->type) {
	case SCTP_PARAM_IPV4_ADDRESS:
	case SCTP_PARAM_IPV6_ADDRESS:
	case SCTP_PARAM_COOKIE_PRESERVATIVE:
	case SCTP_PARAM_SUPPORTED_ADDRESS_TYPES:
	case SCTP_PARAM_STATE_COOKIE:
	case SCTP_PARAM_HEARTBEAT_INFO:
	case SCTP_PARAM_UNRECOGNIZED_PARAMETERS:
	case SCTP_PARAM_ECN_CAPABLE:
	case SCTP_PARAM_ADAPTATION_LAYER_IND:
		break;

	case SCTP_PARAM_SUPPORTED_EXT:
		if (!sctp_verify_ext_param(param))
			return SCTP_IERROR_ABORT;
		break;

	case SCTP_PARAM_SET_PRIMARY:
		if (sctp_addip_enable)
			break;
		goto fallthrough;

	case SCTP_PARAM_HOST_NAME_ADDRESS:
		/* Tell the peer, we won't support this param.  */
		sctp_process_hn_param(asoc, param, chunk, err_chunk);
		retval = SCTP_IERROR_ABORT;
		break;

	case SCTP_PARAM_FWD_TSN_SUPPORT:
		if (sctp_prsctp_enable)
			break;
		goto fallthrough;

	case SCTP_PARAM_RANDOM:
		if (!sctp_auth_enable)
			goto fallthrough;

		/* SCTP-AUTH: Secion 6.1
		 * If the random number is not 32 byte long the association
		 * MUST be aborted.  The ABORT chunk SHOULD contain the error
		 * cause 'Protocol Violation'.
		 */
		if (SCTP_AUTH_RANDOM_LENGTH !=
			ntohs(param.p->length) - sizeof(sctp_paramhdr_t)) {
			sctp_process_inv_paramlength(asoc, param.p,
							chunk, err_chunk);
			retval = SCTP_IERROR_ABORT;
		}
		break;

	case SCTP_PARAM_CHUNKS:
		if (!sctp_auth_enable)
			goto fallthrough;

		/* SCTP-AUTH: Section 3.2
		 * The CHUNKS parameter MUST be included once in the INIT or
		 *  INIT-ACK chunk if the sender wants to receive authenticated
		 *  chunks.  Its maximum length is 260 bytes.
		 */
		if (260 < ntohs(param.p->length)) {
			sctp_process_inv_paramlength(asoc, param.p,
						     chunk, err_chunk);
			retval = SCTP_IERROR_ABORT;
		}
		break;

	case SCTP_PARAM_HMAC_ALGO:
		if (!sctp_auth_enable)
			goto fallthrough;

		hmacs = (struct sctp_hmac_algo_param *)param.p;
		n_elt = (ntohs(param.p->length) - sizeof(sctp_paramhdr_t)) >> 1;

		/* SCTP-AUTH: Section 6.1
		 * The HMAC algorithm based on SHA-1 MUST be supported and
		 * included in the HMAC-ALGO parameter.
		 */
		for (i = 0; i < n_elt; i++) {
			id = ntohs(hmacs->hmac_ids[i]);

			if (id == SCTP_AUTH_HMAC_ID_SHA1)
				break;
		}

		if (id != SCTP_AUTH_HMAC_ID_SHA1) {
			sctp_process_inv_paramlength(asoc, param.p, chunk,
						     err_chunk);
			retval = SCTP_IERROR_ABORT;
		}
		break;
fallthrough:
	default:
		SCTP_DEBUG_PRINTK("Unrecognized param: %d for chunk %d.\n",
				ntohs(param.p->type), cid);
		retval = sctp_process_unk_param(asoc, param, chunk, err_chunk);
		break;
	}
	return retval;
}
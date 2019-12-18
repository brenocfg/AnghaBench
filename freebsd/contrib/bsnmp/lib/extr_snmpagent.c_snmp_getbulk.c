#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct snmp_pdu {size_t error_status; size_t nbindings; size_t error_index; TYPE_2__* bindings; } ;
struct TYPE_5__ {void* data; } ;
struct context {TYPE_1__ ctx; } ;
struct asn_buf {int dummy; } ;
typedef  enum snmp_ret { ____Placeholder_snmp_ret } snmp_ret ;
typedef  enum asn_err { ____Placeholder_asn_err } asn_err ;
typedef  int /*<<< orphan*/  context ;
struct TYPE_6__ {scalar_t__ syntax; } ;

/* Variables and functions */
 int ASN_ERR_EOBUF ; 
 int ASN_ERR_OK ; 
 int /*<<< orphan*/  GET ; 
 scalar_t__ SNMP_CODE_OK ; 
 void* SNMP_ERR_GENERR ; 
 size_t SNMP_MAX_BINDINGS ; 
 int SNMP_RET_ERR ; 
 int SNMP_RET_IGN ; 
 int SNMP_RET_OK ; 
 scalar_t__ SNMP_SYNTAX_ENDOFMIBVIEW ; 
 scalar_t__ TR (int /*<<< orphan*/ ) ; 
 int do_getnext (struct context*,TYPE_2__*,TYPE_2__*,struct snmp_pdu*) ; 
 int /*<<< orphan*/  memset (struct context*,int /*<<< orphan*/ ,int) ; 
 int snmp_binding_encode (struct asn_buf*,TYPE_2__*) ; 
 int /*<<< orphan*/  snmp_debug (char*,...) ; 
 scalar_t__ snmp_fix_encoding (struct asn_buf*,struct snmp_pdu*) ; 
 int /*<<< orphan*/  snmp_pdu_create_response (struct snmp_pdu*,struct snmp_pdu*) ; 
 scalar_t__ snmp_pdu_encode_header (struct asn_buf*,struct snmp_pdu*) ; 
 int /*<<< orphan*/  snmp_pdu_free (struct snmp_pdu*) ; 

enum snmp_ret
snmp_getbulk(struct snmp_pdu *pdu, struct asn_buf *resp_b,
    struct snmp_pdu *resp, void *data)
{
	struct context context;
	u_int i;
	int cnt;
	u_int non_rep;
	int eomib;
	enum snmp_ret result;
	enum asn_err err;

	memset(&context, 0, sizeof(context));
	context.ctx.data = data;

	snmp_pdu_create_response(pdu, resp);

	if (snmp_pdu_encode_header(resp_b, resp) != SNMP_CODE_OK)
		/* cannot even encode header - very bad */
		return (SNMP_RET_IGN);

	if ((non_rep = pdu->error_status) > pdu->nbindings)
		non_rep = pdu->nbindings;

	/* non-repeaters */
	for (i = 0; i < non_rep; i++) {
		result = do_getnext(&context, &pdu->bindings[i],
		    &resp->bindings[resp->nbindings], pdu);

		if (result != SNMP_RET_OK) {
			pdu->error_index = i + 1;
			snmp_pdu_free(resp);
			return (result);
		}

		err = snmp_binding_encode(resp_b,
		    &resp->bindings[resp->nbindings++]);

		if (err == ASN_ERR_EOBUF)
			goto done;

		if (err != ASN_ERR_OK) {
			if (TR(GET))
				snmp_debug("getnext: binding encoding: %u", err);
			pdu->error_status = SNMP_ERR_GENERR;
			pdu->error_index = i + 1;
			snmp_pdu_free(resp);
			return (SNMP_RET_ERR);
		}
	}

	if (non_rep == pdu->nbindings)
		goto done;

	/* repeates */
	for (cnt = 0; cnt < pdu->error_index; cnt++) {
		eomib = 1;
		for (i = non_rep; i < pdu->nbindings; i++) {

			if (resp->nbindings == SNMP_MAX_BINDINGS)
				/* PDU is full */
				goto done;

			if (cnt == 0)
				result = do_getnext(&context, &pdu->bindings[i],
				    &resp->bindings[resp->nbindings], pdu);
			else
				result = do_getnext(&context,
				    &resp->bindings[resp->nbindings -
				    (pdu->nbindings - non_rep)],
				    &resp->bindings[resp->nbindings], pdu);

			if (result != SNMP_RET_OK) {
				pdu->error_index = i + 1;
				snmp_pdu_free(resp);
				return (result);
			}
			if (resp->bindings[resp->nbindings].syntax !=
			    SNMP_SYNTAX_ENDOFMIBVIEW)
				eomib = 0;

			err = snmp_binding_encode(resp_b,
			    &resp->bindings[resp->nbindings++]);

			if (err == ASN_ERR_EOBUF)
				goto done;

			if (err != ASN_ERR_OK) {
				if (TR(GET))
					snmp_debug("getnext: binding encoding: %u", err);
				pdu->error_status = SNMP_ERR_GENERR;
				pdu->error_index = i + 1;
				snmp_pdu_free(resp);
				return (SNMP_RET_ERR);
			}
		}
		if (eomib)
			break;
	}

  done:
	if (snmp_fix_encoding(resp_b, resp) != SNMP_CODE_OK) {
		snmp_debug("getnext: failed to encode PDU");
		return (SNMP_RET_ERR);
	}

	return (SNMP_RET_OK);
}
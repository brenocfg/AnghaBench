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
typedef  size_t u_int ;
struct snmp_pdu {size_t nbindings; size_t error_index; int /*<<< orphan*/  error_status; int /*<<< orphan*/ * bindings; } ;
struct TYPE_2__ {void* data; } ;
struct context {TYPE_1__ ctx; } ;
struct asn_buf {int dummy; } ;
typedef  enum snmp_ret { ____Placeholder_snmp_ret } snmp_ret ;
typedef  enum asn_err { ____Placeholder_asn_err } asn_err ;
typedef  int /*<<< orphan*/  context ;

/* Variables and functions */
 int ASN_ERR_EOBUF ; 
 int ASN_ERR_OK ; 
 int /*<<< orphan*/  GET ; 
 scalar_t__ SNMP_CODE_OK ; 
 int /*<<< orphan*/  SNMP_ERR_GENERR ; 
 int /*<<< orphan*/  SNMP_ERR_TOOBIG ; 
 int SNMP_RET_ERR ; 
 int SNMP_RET_IGN ; 
 int SNMP_RET_OK ; 
 scalar_t__ TR (int /*<<< orphan*/ ) ; 
 int do_getnext (struct context*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct snmp_pdu*) ; 
 int /*<<< orphan*/  memset (struct context*,int /*<<< orphan*/ ,int) ; 
 int snmp_binding_encode (struct asn_buf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snmp_debug (char*,...) ; 
 scalar_t__ snmp_fix_encoding (struct asn_buf*,struct snmp_pdu*) ; 
 int /*<<< orphan*/  snmp_pdu_create_response (struct snmp_pdu*,struct snmp_pdu*) ; 
 scalar_t__ snmp_pdu_encode_header (struct asn_buf*,struct snmp_pdu*) ; 
 int /*<<< orphan*/  snmp_pdu_free (struct snmp_pdu*) ; 

enum snmp_ret
snmp_getnext(struct snmp_pdu *pdu, struct asn_buf *resp_b,
    struct snmp_pdu *resp, void *data)
{
	struct context context;
	u_int i;
	enum asn_err err;
	enum snmp_ret result;

	memset(&context, 0, sizeof(context));
	context.ctx.data = data;

	snmp_pdu_create_response(pdu, resp);

	if (snmp_pdu_encode_header(resp_b, resp))
		return (SNMP_RET_IGN);

	for (i = 0; i < pdu->nbindings; i++) {
		result = do_getnext(&context, &pdu->bindings[i],
		    &resp->bindings[i], pdu);

		if (result != SNMP_RET_OK) {
			pdu->error_index = i + 1;
			snmp_pdu_free(resp);
			return (result);
		}

		resp->nbindings++;

		err = snmp_binding_encode(resp_b, &resp->bindings[i]);

		if (err == ASN_ERR_EOBUF) {
			pdu->error_status = SNMP_ERR_TOOBIG;
			pdu->error_index = 0;
			snmp_pdu_free(resp);
			return (SNMP_RET_ERR);
		}
		if (err != ASN_ERR_OK) {
			if (TR(GET))
				snmp_debug("getnext: binding encoding: %u", err);
			pdu->error_status = SNMP_ERR_GENERR;
			pdu->error_index = i + 1;
			snmp_pdu_free(resp);
			return (SNMP_RET_ERR);
		}
	}

	if (snmp_fix_encoding(resp_b, resp) != SNMP_CODE_OK) {
		snmp_debug("getnext: failed to encode PDU");
		return (SNMP_RET_ERR);
	}

	return (SNMP_RET_OK);
}
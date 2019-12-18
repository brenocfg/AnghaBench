#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct snmp_value {scalar_t__ syntax; int /*<<< orphan*/  var; } ;
struct snmp_pdu {size_t nbindings; scalar_t__ version; size_t error_index; int error_status; struct snmp_value* bindings; } ;
struct TYPE_7__ {int /*<<< orphan*/  len; } ;
struct snmp_node {scalar_t__ type; int flags; scalar_t__ syntax; int (* op ) (TYPE_2__*,struct snmp_value*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  index; TYPE_1__ oid; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int code; size_t var_index; int /*<<< orphan*/ * scratch; void* data; } ;
struct context {TYPE_2__ ctx; int /*<<< orphan*/ * scratch; struct snmp_node** node; int /*<<< orphan*/  dlist; } ;
struct asn_buf {int dummy; } ;
typedef  enum snmp_syntax { ____Placeholder_snmp_syntax } snmp_syntax ;
typedef  enum snmp_ret { ____Placeholder_snmp_ret } snmp_ret ;
typedef  enum asn_err { ____Placeholder_asn_err } asn_err ;
typedef  int /*<<< orphan*/  context ;

/* Variables and functions */
 int ASN_ERR_EOBUF ; 
 int ASN_ERR_OK ; 
 int /*<<< orphan*/  SET ; 
 scalar_t__ SNMP_CODE_OK ; 
#define  SNMP_ERR_AUTH_ERR 140 
 void* SNMP_ERR_BADVALUE ; 
#define  SNMP_ERR_COMMIT_FAILED 139 
 void* SNMP_ERR_GENERR ; 
#define  SNMP_ERR_INCONS_NAME 138 
#define  SNMP_ERR_INCONS_VALUE 137 
 int SNMP_ERR_NOERROR ; 
 void* SNMP_ERR_NOSUCHNAME ; 
#define  SNMP_ERR_NOT_WRITEABLE 136 
#define  SNMP_ERR_NO_ACCESS 135 
#define  SNMP_ERR_NO_CREATION 134 
#define  SNMP_ERR_RES_UNAVAIL 133 
 int SNMP_ERR_TOOBIG ; 
#define  SNMP_ERR_UNDO_FAILED 132 
#define  SNMP_ERR_WRONG_ENCODING 131 
#define  SNMP_ERR_WRONG_LENGTH 130 
#define  SNMP_ERR_WRONG_TYPE 129 
#define  SNMP_ERR_WRONG_VALUE 128 
 int SNMP_NODE_CANSET ; 
 scalar_t__ SNMP_NODE_LEAF ; 
 int /*<<< orphan*/  SNMP_OP_COMMIT ; 
 int /*<<< orphan*/  SNMP_OP_SET ; 
 int SNMP_RET_ERR ; 
 int SNMP_RET_IGN ; 
 int SNMP_RET_OK ; 
 int SNMP_SYNTAX_NOSUCHOBJECT ; 
 scalar_t__ SNMP_V1 ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 scalar_t__ TR (int /*<<< orphan*/ ) ; 
 int asn_oid2str_r (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct snmp_node* find_node (struct snmp_value*,int*) ; 
 struct snmp_node* find_subnode (struct snmp_value*) ; 
 int /*<<< orphan*/  memset (struct context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oidbuf ; 
 int /*<<< orphan*/  rollback (struct context*,struct snmp_pdu*,size_t) ; 
 int snmp_binding_encode (struct asn_buf*,struct snmp_value*) ; 
 int /*<<< orphan*/  snmp_debug (char*,...) ; 
 int snmp_dep_commit (TYPE_2__*) ; 
 int /*<<< orphan*/  snmp_dep_finish (TYPE_2__*) ; 
 int snmp_dep_rollback (TYPE_2__*) ; 
 int /*<<< orphan*/  snmp_error (char*,...) ; 
 scalar_t__ snmp_fix_encoding (struct asn_buf*,struct snmp_pdu*) ; 
 int /*<<< orphan*/  snmp_pdu_create_response (struct snmp_pdu*,struct snmp_pdu*) ; 
 scalar_t__ snmp_pdu_encode_header (struct asn_buf*,struct snmp_pdu*) ; 
 int /*<<< orphan*/  snmp_pdu_free (struct snmp_pdu*) ; 
 scalar_t__ snmp_value_copy (struct snmp_value*,struct snmp_value*) ; 
 int stub1 (TYPE_2__*,struct snmp_value*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (TYPE_2__*,struct snmp_value*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

enum snmp_ret
snmp_set(struct snmp_pdu *pdu, struct asn_buf *resp_b,
    struct snmp_pdu *resp, void *data)
{
	int ret;
	u_int i;
	enum asn_err asnerr;
	struct context context;
	const struct snmp_node *np;
	struct snmp_value *b;
	enum snmp_syntax except;

	memset(&context, 0, sizeof(context));
	TAILQ_INIT(&context.dlist);
	context.ctx.data = data;

	snmp_pdu_create_response(pdu, resp);

	if (snmp_pdu_encode_header(resp_b, resp))
		return (SNMP_RET_IGN);

	/*
	 * 1. Find all nodes, check that they are writeable and
	 *    that the syntax is ok, copy over the binding to the response.
	 */
	for (i = 0; i < pdu->nbindings; i++) {
		b = &pdu->bindings[i];

		if ((np = context.node[i] = find_node(b, &except)) == NULL) {
			/* not found altogether or LEAF with wrong index */
			if (TR(SET))
				snmp_debug("set: node not found %s",
				    asn_oid2str_r(&b->var, oidbuf));
			if (pdu->version == SNMP_V1) {
				pdu->error_index = i + 1;
				pdu->error_status = SNMP_ERR_NOSUCHNAME;
			} else if ((np = find_subnode(b)) != NULL) {
				/* 2. intermediate object */
				pdu->error_index = i + 1;
				pdu->error_status = SNMP_ERR_NOT_WRITEABLE;
			} else if (except == SNMP_SYNTAX_NOSUCHOBJECT) {
				pdu->error_index = i + 1;
				pdu->error_status = SNMP_ERR_NO_ACCESS;
			} else {
				pdu->error_index = i + 1;
				pdu->error_status = SNMP_ERR_NO_CREATION;
			}
			snmp_pdu_free(resp);
			return (SNMP_RET_ERR);
		}
		/*
		 * 2. write/createable?
		 * Can check this for leafs only, because in v2 we have
		 * to differentiate between NOT_WRITEABLE and NO_CREATION
		 * and only the action routine for COLUMNS knows, whether
		 * a column exists.
		 */
		if (np->type == SNMP_NODE_LEAF &&
		    !(np->flags & SNMP_NODE_CANSET)) {
			if (pdu->version == SNMP_V1) {
				pdu->error_index = i + 1;
				pdu->error_status = SNMP_ERR_NOSUCHNAME;
			} else {
				pdu->error_index = i + 1;
				pdu->error_status = SNMP_ERR_NOT_WRITEABLE;
			}
			snmp_pdu_free(resp);
			return (SNMP_RET_ERR);
		}
		/*
		 * 3. Ensure the right syntax
		 */
		if (np->syntax != b->syntax) {
			if (pdu->version == SNMP_V1) {
				pdu->error_index = i + 1;
				pdu->error_status = SNMP_ERR_BADVALUE; /* v2: wrongType */
			} else {
				pdu->error_index = i + 1;
				pdu->error_status = SNMP_ERR_WRONG_TYPE;
			}
			snmp_pdu_free(resp);
			return (SNMP_RET_ERR);
		}
		/*
		 * 4. Copy binding
		 */
		if (snmp_value_copy(&resp->bindings[i], b)) {
			pdu->error_index = i + 1;
			pdu->error_status = SNMP_ERR_GENERR;
			snmp_pdu_free(resp);
			return (SNMP_RET_ERR);
		}
		asnerr = snmp_binding_encode(resp_b, &resp->bindings[i]);
		if (asnerr == ASN_ERR_EOBUF) {
			pdu->error_index = i + 1;
			pdu->error_status = SNMP_ERR_TOOBIG;
			snmp_pdu_free(resp);
			return (SNMP_RET_ERR);
		} else if (asnerr != ASN_ERR_OK) {
			pdu->error_index = i + 1;
			pdu->error_status = SNMP_ERR_GENERR;
			snmp_pdu_free(resp);
			return (SNMP_RET_ERR);
		}
		resp->nbindings++;
	}

	context.ctx.code = SNMP_RET_OK;

	/*
	 * 2. Call the SET method for each node. If a SET fails, rollback
	 *    everything. Map error codes depending on the version.
	 */
	for (i = 0; i < pdu->nbindings; i++) {
		b = &pdu->bindings[i];
		np = context.node[i];

		context.ctx.var_index = i + 1;
		context.ctx.scratch = &context.scratch[i];

		ret = (*np->op)(&context.ctx, b, np->oid.len, np->index,
		    SNMP_OP_SET);

		if (TR(SET))
			snmp_debug("set: action %s returns %d", np->name, ret);

		if (pdu->version == SNMP_V1) {
			switch (ret) {
			  case SNMP_ERR_NO_ACCESS:
				ret = SNMP_ERR_NOSUCHNAME;
				break;
			  case SNMP_ERR_WRONG_TYPE:
				/* should no happen */
				ret = SNMP_ERR_BADVALUE;
				break;
			  case SNMP_ERR_WRONG_LENGTH:
				ret = SNMP_ERR_BADVALUE;
				break;
			  case SNMP_ERR_WRONG_ENCODING:
				/* should not happen */
				ret = SNMP_ERR_BADVALUE;
				break;
			  case SNMP_ERR_WRONG_VALUE:
				ret = SNMP_ERR_BADVALUE;
				break;
			  case SNMP_ERR_NO_CREATION:
				ret = SNMP_ERR_NOSUCHNAME;
				break;
			  case SNMP_ERR_INCONS_VALUE:
				ret = SNMP_ERR_BADVALUE;
				break;
			  case SNMP_ERR_RES_UNAVAIL:
				ret = SNMP_ERR_GENERR;
				break;
			  case SNMP_ERR_COMMIT_FAILED:
				ret = SNMP_ERR_GENERR;
				break;
			  case SNMP_ERR_UNDO_FAILED:
				ret = SNMP_ERR_GENERR;
				break;
			  case SNMP_ERR_AUTH_ERR:
				/* should not happen */
				ret = SNMP_ERR_GENERR;
				break;
			  case SNMP_ERR_NOT_WRITEABLE:
				ret = SNMP_ERR_NOSUCHNAME;
				break;
			  case SNMP_ERR_INCONS_NAME:
				ret = SNMP_ERR_BADVALUE;
				break;
			}
		}
		if (ret != SNMP_ERR_NOERROR) {
			pdu->error_index = i + 1;
			pdu->error_status = ret;

			rollback(&context, pdu, i);
			snmp_pdu_free(resp);

			context.ctx.code = SNMP_RET_ERR;

			goto errout;
		}
	}

	/*
	 * 3. Call dependencies
	 */
	if (TR(SET))
		snmp_debug("set: set operations ok");

	if ((ret = snmp_dep_commit(&context.ctx)) != SNMP_ERR_NOERROR) {
		pdu->error_status = ret;
		pdu->error_index = context.ctx.var_index;

		if ((ret = snmp_dep_rollback(&context.ctx)) != SNMP_ERR_NOERROR) {
			if (pdu->version != SNMP_V1) {
				pdu->error_status = SNMP_ERR_UNDO_FAILED;
				pdu->error_index = 0;
			}
		}
		rollback(&context, pdu, i);
		snmp_pdu_free(resp);

		context.ctx.code = SNMP_RET_ERR;

		goto errout;
	}

	/*
	 * 4. Commit and copy values from the original packet to the response.
	 *    This is not the commit operation from RFC 1905 but rather an
	 *    'FREE RESOURCES' operation. It shouldn't fail.
	 */
	if (TR(SET))
		snmp_debug("set: commiting");

	for (i = 0; i < pdu->nbindings; i++) {
		b = &resp->bindings[i];
		np = context.node[i];

		context.ctx.var_index = i + 1;
		context.ctx.scratch = &context.scratch[i];

		ret = (*np->op)(&context.ctx, b, np->oid.len, np->index,
		    SNMP_OP_COMMIT);

		if (ret != SNMP_ERR_NOERROR)
			snmp_error("set: commit failed (%d) on"
			    " variable %s index %u", ret,
			    asn_oid2str_r(&b->var, oidbuf), i);
	}

	if (snmp_fix_encoding(resp_b, resp) != SNMP_CODE_OK) {
		snmp_error("set: fix_encoding failed");
		snmp_pdu_free(resp);
		context.ctx.code = SNMP_RET_IGN;
	}

	/*
	 * Done
	 */
  errout:
	snmp_dep_finish(&context.ctx);

	if (TR(SET))
		snmp_debug("set: returning %d", context.ctx.code);

	return (context.ctx.code);
}
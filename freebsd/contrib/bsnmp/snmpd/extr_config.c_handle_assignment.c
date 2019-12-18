#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct TYPE_4__ {scalar_t__ len; int /*<<< orphan*/ * subs; } ;
struct snmp_value {TYPE_1__ var; } ;
struct snmp_node {scalar_t__ type; char* name; int (* op ) (TYPE_2__*,struct snmp_value*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  index; TYPE_1__ oid; } ;
struct assign {char* node_name; struct snmp_value value; int /*<<< orphan*/  scratch; } ;
struct asn_oid {int len; int /*<<< orphan*/ * subs; } ;
typedef  int /*<<< orphan*/  nodename ;
struct TYPE_5__ {scalar_t__ var_index; int /*<<< orphan*/ * scratch; } ;

/* Variables and functions */
 scalar_t__ ASN_MAXOIDLEN ; 
 scalar_t__ SNMP_NODE_LEAF ; 
 int /*<<< orphan*/  SNMP_OP_SET ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct assign*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asn_oid2str (struct asn_oid*) ; 
 int /*<<< orphan*/  assigns ; 
 int /*<<< orphan*/  free (struct assign*) ; 
 int /*<<< orphan*/  link ; 
 struct assign* malloc (int) ; 
 int /*<<< orphan*/  report (char*,...) ; 
 TYPE_2__* snmp_ctx ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int stub1 (TYPE_2__*,struct snmp_value*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
handle_assignment(const struct snmp_node *node, struct asn_oid *vindex,
    const struct snmp_value *value)
{
	u_int i;
	int err;
	struct assign *tp;
	char nodename[100];

	if (node->type == SNMP_NODE_LEAF) {
		/* index must be one single zero or no index at all */
		if (vindex->len > 1 || (vindex->len == 1 &&
		    vindex->subs[0] != 0))
			report("bad index on leaf node");
		vindex->len = 1;
		vindex->subs[0] = 0;
	} else {
		/* resulting oid must not be too long */
		if (node->oid.len + vindex->len > ASN_MAXOIDLEN)
			report("resulting OID too long");
	}

	/*
	 * Get the next assignment entry for the transaction.
	 */
	if ((tp = malloc(sizeof(*tp))) == NULL)
		report("%m");

	tp->value = *value;
	tp->node_name = node->name;

	/*
	 * Build the OID
	 */
	tp->value.var = node->oid;
	for (i = 0; i < vindex->len; i++)
		tp->value.var.subs[tp->value.var.len++] = vindex->subs[i];

	/*
	 * Puzzle together the variables for the call and call the
	 * set routine. The set routine may make our node pointer
	 * invalid (if we happend to call the module loader) so
	 * get a copy of the node name beforehands.
	 */
	snprintf(nodename, sizeof(nodename), "%s", node->name);
	snmp_ctx->scratch = &tp->scratch;
	snmp_ctx->var_index = 0;
	err = (*node->op)(snmp_ctx, &tp->value, node->oid.len, node->index,
	    SNMP_OP_SET);
	if (err != 0) {
		free(tp);
		report("assignment to %s.%s returns %d", nodename,
		    asn_oid2str(vindex), err);
	}

	TAILQ_INSERT_TAIL(&assigns, tp, link);
}
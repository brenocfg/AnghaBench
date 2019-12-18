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
struct TYPE_4__ {int /*<<< orphan*/  len; } ;
struct snmp_node {scalar_t__ name; int /*<<< orphan*/  index; TYPE_1__ oid; int /*<<< orphan*/  (* op ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct assign {scalar_t__ node_name; int /*<<< orphan*/  value; int /*<<< orphan*/  scratch; } ;
struct TYPE_5__ {int /*<<< orphan*/ * scratch; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  SNMP_OP_COMMIT ; 
 struct assign* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct assign*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assigns ; 
 int /*<<< orphan*/  free (struct assign*) ; 
 int /*<<< orphan*/  link ; 
 TYPE_2__* snmp_ctx ; 
 int /*<<< orphan*/  snmp_value_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 
 struct snmp_node* tree ; 
 size_t tree_size ; 

__attribute__((used)) static void
do_commit(void)
{
	struct assign *tp;
	struct snmp_node *node;

	while ((tp = TAILQ_FIRST(&assigns)) != NULL) {
		TAILQ_REMOVE(&assigns, tp, link);
		for (node = tree; node < &tree[tree_size]; node++)
			if (node->name == tp->node_name) {
				snmp_ctx->scratch = &tp->scratch;
				(void)(*node->op)(snmp_ctx, &tp->value,
				    node->oid.len, node->index, SNMP_OP_COMMIT);
				break;
			}
		if (node == &tree[tree_size])
			syslog(LOG_ERR, "failed to find node for commit");
		snmp_value_free(&tp->value);
		free(tp);
	}
}
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
typedef  int u16 ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int specified; } ;
struct avtab_node {TYPE_2__ datum; TYPE_1__ key; } ;
struct avtab_key {int /*<<< orphan*/  specified; } ;
struct avtab {int dummy; } ;
struct av_decision {int /*<<< orphan*/  auditallow; int /*<<< orphan*/  auditdeny; int /*<<< orphan*/  allowed; } ;

/* Variables and functions */
 int AVTAB_ALLOWED ; 
 int AVTAB_AUDITALLOW ; 
 int AVTAB_AUDITDENY ; 
 int AVTAB_ENABLED ; 
 struct avtab_node* avtab_search_node (struct avtab*,struct avtab_key*) ; 
 struct avtab_node* avtab_search_node_next (struct avtab_node*,int /*<<< orphan*/ ) ; 

void cond_compute_av(struct avtab *ctab, struct avtab_key *key, struct av_decision *avd)
{
	struct avtab_node *node;

	if (!ctab || !key || !avd)
		return;

	for (node = avtab_search_node(ctab, key); node;
				node = avtab_search_node_next(node, key->specified)) {
		if ((u16)(AVTAB_ALLOWED|AVTAB_ENABLED) ==
		    (node->key.specified & (AVTAB_ALLOWED|AVTAB_ENABLED)))
			avd->allowed |= node->datum.data;
		if ((u16)(AVTAB_AUDITDENY|AVTAB_ENABLED) ==
		    (node->key.specified & (AVTAB_AUDITDENY|AVTAB_ENABLED)))
			/* Since a '0' in an auditdeny mask represents a
			 * permission we do NOT want to audit (dontaudit), we use
			 * the '&' operand to ensure that all '0's in the mask
			 * are retained (much unlike the allow and auditallow cases).
			 */
			avd->auditdeny &= node->datum.data;
		if ((u16)(AVTAB_AUDITALLOW|AVTAB_ENABLED) ==
		    (node->key.specified & (AVTAB_AUDITALLOW|AVTAB_ENABLED)))
			avd->auditallow |= node->datum.data;
	}
	return;
}
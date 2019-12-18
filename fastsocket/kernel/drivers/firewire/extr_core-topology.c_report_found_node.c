#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct fw_node {scalar_t__ phy_speed; scalar_t__ max_speed; int b_path; } ;
struct fw_card {scalar_t__ bm_retries; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_NODE_CREATED ; 
 scalar_t__ SCODE_BETA ; 
 int /*<<< orphan*/  fw_node_event (struct fw_card*,struct fw_node*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void report_found_node(struct fw_card *card,
			      struct fw_node *node, struct fw_node *parent)
{
	int b_path = (node->phy_speed == SCODE_BETA);

	if (parent != NULL) {
		/* min() macro doesn't work here with gcc 3.4 */
		node->max_speed = parent->max_speed < node->phy_speed ?
					parent->max_speed : node->phy_speed;
		node->b_path = parent->b_path && b_path;
	} else {
		node->max_speed = node->phy_speed;
		node->b_path = b_path;
	}

	fw_node_event(card, node, FW_NODE_CREATED);

	/* Topology has changed - reset bus manager retry counter */
	card->bm_retries = 0;
}
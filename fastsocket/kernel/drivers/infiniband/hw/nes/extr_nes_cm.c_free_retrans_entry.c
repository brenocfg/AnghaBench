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
struct nes_timer_entry {int /*<<< orphan*/  skb; } ;
struct nes_cm_node {int /*<<< orphan*/  cm_core; struct nes_timer_entry* send_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nes_timer_entry*) ; 
 int /*<<< orphan*/  rem_ref_cm_node (int /*<<< orphan*/ ,struct nes_cm_node*) ; 

__attribute__((used)) static void free_retrans_entry(struct nes_cm_node *cm_node)
{
	struct nes_timer_entry *send_entry;

	send_entry = cm_node->send_entry;
	if (send_entry) {
		cm_node->send_entry = NULL;
		dev_kfree_skb_any(send_entry->skb);
		kfree(send_entry);
		rem_ref_cm_node(cm_node->cm_core, cm_node);
	}
}
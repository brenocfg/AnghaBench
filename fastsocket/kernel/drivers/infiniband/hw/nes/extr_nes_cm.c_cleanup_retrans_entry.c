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
struct nes_cm_node {int /*<<< orphan*/  retrans_list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_retrans_entry (struct nes_cm_node*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void cleanup_retrans_entry(struct nes_cm_node *cm_node)
{
	unsigned long flags;

	spin_lock_irqsave(&cm_node->retrans_list_lock, flags);
	free_retrans_entry(cm_node);
	spin_unlock_irqrestore(&cm_node->retrans_list_lock, flags);
}
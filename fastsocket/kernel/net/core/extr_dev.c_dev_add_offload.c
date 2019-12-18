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
struct packet_offload {int /*<<< orphan*/  list; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,struct list_head*) ; 
 struct list_head offload_base ; 
 int /*<<< orphan*/  offload_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void dev_add_offload(struct packet_offload *po)
{
	struct list_head *head = &offload_base;

	spin_lock(&offload_lock);
	list_add_rcu(&po->list, head);
	spin_unlock(&offload_lock);
}
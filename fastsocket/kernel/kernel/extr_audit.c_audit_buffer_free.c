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
struct audit_buffer {int /*<<< orphan*/  list; scalar_t__ skb; } ;

/* Variables and functions */
 scalar_t__ AUDIT_MAXFREE ; 
 int /*<<< orphan*/  audit_freelist ; 
 scalar_t__ audit_freelist_count ; 
 int /*<<< orphan*/  audit_freelist_lock ; 
 int /*<<< orphan*/  kfree (struct audit_buffer*) ; 
 int /*<<< orphan*/  kfree_skb (scalar_t__) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void audit_buffer_free(struct audit_buffer *ab)
{
	unsigned long flags;

	if (!ab)
		return;

	if (ab->skb)
		kfree_skb(ab->skb);

	spin_lock_irqsave(&audit_freelist_lock, flags);
	if (audit_freelist_count > AUDIT_MAXFREE)
		kfree(ab);
	else {
		audit_freelist_count++;
		list_add(&ab->list, &audit_freelist);
	}
	spin_unlock_irqrestore(&audit_freelist_lock, flags);
}
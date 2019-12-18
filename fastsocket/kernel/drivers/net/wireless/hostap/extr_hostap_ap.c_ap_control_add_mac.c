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
typedef  int /*<<< orphan*/  u8 ;
struct mac_restrictions {int /*<<< orphan*/  lock; int /*<<< orphan*/  entries; int /*<<< orphan*/  mac_list; } ;
struct mac_entry {int /*<<< orphan*/  list; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mac_entry* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int ap_control_add_mac(struct mac_restrictions *mac_restrictions, u8 *mac)
{
	struct mac_entry *entry;

	entry = kmalloc(sizeof(struct mac_entry), GFP_KERNEL);
	if (entry == NULL)
		return -ENOMEM;

	memcpy(entry->addr, mac, ETH_ALEN);

	spin_lock_bh(&mac_restrictions->lock);
	list_add_tail(&entry->list, &mac_restrictions->mac_list);
	mac_restrictions->entries++;
	spin_unlock_bh(&mac_restrictions->lock);

	return 0;
}
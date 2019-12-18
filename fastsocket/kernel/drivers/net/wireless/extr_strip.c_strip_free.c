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
struct strip {int /*<<< orphan*/  dev; scalar_t__ magic; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strip_lock ; 

__attribute__((used)) static void strip_free(struct strip *strip_info)
{
	spin_lock_bh(&strip_lock);
	list_del_rcu(&strip_info->list);
	spin_unlock_bh(&strip_lock);

	strip_info->magic = 0;

	free_netdev(strip_info->dev);
}
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
struct zcrypt_ops {int /*<<< orphan*/  list; scalar_t__ owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zcrypt_ops_list ; 
 int /*<<< orphan*/  zcrypt_ops_list_lock ; 

void zcrypt_msgtype_register(struct zcrypt_ops *zops)
{
	if (zops->owner) {
		spin_lock_bh(&zcrypt_ops_list_lock);
		list_add_tail(&zops->list, &zcrypt_ops_list);
		spin_unlock_bh(&zcrypt_ops_list_lock);
	}
}
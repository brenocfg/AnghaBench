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
struct super_block {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_li_request; } ;
struct TYPE_3__ {int /*<<< orphan*/  li_list_mtx; } ;

/* Variables and functions */
 TYPE_2__* EXT4_SB (struct super_block*) ; 
 TYPE_1__* ext4_li_info ; 
 int /*<<< orphan*/  ext4_li_mtx ; 
 int /*<<< orphan*/  ext4_remove_li_request (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ext4_unregister_li_request(struct super_block *sb)
{
	mutex_lock(&ext4_li_mtx);
	if (!ext4_li_info) {
		mutex_unlock(&ext4_li_mtx);
		return;
	}

	mutex_lock(&ext4_li_info->li_list_mtx);
	ext4_remove_li_request(EXT4_SB(sb)->s_li_request);
	mutex_unlock(&ext4_li_info->li_list_mtx);
	mutex_unlock(&ext4_li_mtx);
}
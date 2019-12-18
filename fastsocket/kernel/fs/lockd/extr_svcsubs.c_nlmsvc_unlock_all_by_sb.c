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
struct super_block {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int nlm_traverse_files (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsvc_always_match ; 
 int /*<<< orphan*/  nlmsvc_match_sb ; 

int
nlmsvc_unlock_all_by_sb(struct super_block *sb)
{
	int ret;

	ret = nlm_traverse_files(sb, nlmsvc_always_match, nlmsvc_match_sb);
	return ret ? -EIO : 0;
}
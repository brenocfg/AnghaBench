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
typedef  int /*<<< orphan*/  secno ;

/* Variables and functions */
 int hpfs_alloc_if_possible_nolock (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpfs_lock_creation (struct super_block*) ; 
 int /*<<< orphan*/  hpfs_unlock_creation (struct super_block*) ; 

int hpfs_alloc_if_possible(struct super_block *s, secno sec)
{
	int r;
	hpfs_lock_creation(s);
	r = hpfs_alloc_if_possible_nolock(s, sec);
	hpfs_unlock_creation(s);
	return r;
}
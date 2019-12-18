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
struct btrfs_super_block {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int* btrfs_csum_sizes ; 
 int btrfs_super_csum_type (struct btrfs_super_block*) ; 

__attribute__((used)) static inline int btrfs_super_csum_size(struct btrfs_super_block *s)
{
	int t = btrfs_super_csum_type(s);
	BUG_ON(t >= ARRAY_SIZE(btrfs_csum_sizes));
	return btrfs_csum_sizes[t];
}
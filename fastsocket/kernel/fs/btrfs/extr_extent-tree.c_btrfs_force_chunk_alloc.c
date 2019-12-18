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
typedef  int /*<<< orphan*/  u64 ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHUNK_ALLOC_FORCE ; 
 int do_chunk_alloc (struct btrfs_trans_handle*,struct btrfs_root*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_alloc_profile (struct btrfs_root*,int /*<<< orphan*/ ) ; 

int btrfs_force_chunk_alloc(struct btrfs_trans_handle *trans,
			    struct btrfs_root *root, u64 type)
{
	u64 alloc_flags = get_alloc_profile(root, type);
	return do_chunk_alloc(trans, root, 2 * 1024 * 1024, alloc_flags,
			      CHUNK_ALLOC_FORCE);
}
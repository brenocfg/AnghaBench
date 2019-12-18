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
 int OCFS2_SUBALLOC_ALLOC ; 
 int ocfs2_clusters_to_blocks (struct super_block*,int) ; 

__attribute__((used)) static inline int ocfs2_add_dir_index_credits(struct super_block *sb)
{
	/* 1 block for index, 2 allocs (data, metadata), 1 clusters
	 * worth of blocks for initial extent. */
	return 1 + 2 * OCFS2_SUBALLOC_ALLOC +
		ocfs2_clusters_to_blocks(sb, 1);
}
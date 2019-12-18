#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct super_block {int dummy; } ;
typedef  unsigned int pgoff_t ;
struct TYPE_2__ {unsigned int s_clustersize_bits; } ;

/* Variables and functions */
 TYPE_1__* OCFS2_SB (struct super_block*) ; 
 unsigned int PAGE_CACHE_SHIFT ; 

__attribute__((used)) static inline pgoff_t ocfs2_align_clusters_to_page_index(struct super_block *sb,
							u32 clusters)
{
	unsigned int cbits = OCFS2_SB(sb)->s_clustersize_bits;
        pgoff_t index = clusters;

	if (PAGE_CACHE_SHIFT > cbits) {
		index = (pgoff_t)clusters >> (PAGE_CACHE_SHIFT - cbits);
	} else if (PAGE_CACHE_SHIFT < cbits) {
		index = (pgoff_t)clusters << (cbits - PAGE_CACHE_SHIFT);
	}

	return index;
}
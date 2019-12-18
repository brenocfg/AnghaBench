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
struct inode {int /*<<< orphan*/  i_sb; } ;
typedef  int /*<<< orphan*/  blkcnt_t ;
struct TYPE_4__ {int ip_clusters; } ;
struct TYPE_3__ {int s_clustersize_bits; } ;

/* Variables and functions */
 TYPE_2__* OCFS2_I (struct inode*) ; 
 TYPE_1__* OCFS2_SB (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline blkcnt_t ocfs2_inode_sector_count(struct inode *inode)
{
	int c_to_s_bits = OCFS2_SB(inode->i_sb)->s_clustersize_bits - 9;

	return (blkcnt_t)(OCFS2_I(inode)->ip_clusters << c_to_s_bits);
}
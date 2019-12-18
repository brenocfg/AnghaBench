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
typedef  int /*<<< orphan*/  u32 ;
struct nilfs_palloc_group_desc {int /*<<< orphan*/  pg_nfrees; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_mdt_bgl_lock (struct inode*,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nilfs_palloc_group_desc_add_entries(struct inode *inode,
				    unsigned long group,
				    struct nilfs_palloc_group_desc *desc,
				    u32 n)
{
	spin_lock(nilfs_mdt_bgl_lock(inode, group));
	le32_add_cpu(&desc->pg_nfrees, n);
	spin_unlock(nilfs_mdt_bgl_lock(inode, group));
}
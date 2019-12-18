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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct hugepage_subpool {int dummy; } ;
struct TYPE_2__ {struct hugepage_subpool* spool; } ;

/* Variables and functions */
 TYPE_1__* HUGETLBFS_SB (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct hugepage_subpool *subpool_inode(struct inode *inode)
{
	return HUGETLBFS_SB(inode->i_sb)->spool;
}
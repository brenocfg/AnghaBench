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
struct inode {int dummy; } ;
struct TYPE_2__ {int ip_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int OCFS2_INODE_SYSTEM_FILE ; 
 int ocfs2_ci_is_new (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ocfs2_inode_is_new(struct inode *inode)
{
	/* System files are never "new" as they're written out by
	 * mkfs. This helps us early during mount, before we have the
	 * journal open and j_trans_id could be junk. */
	if (OCFS2_I(inode)->ip_flags & OCFS2_INODE_SYSTEM_FILE)
		return 0;

	return ocfs2_ci_is_new(INODE_CACHE(inode));
}
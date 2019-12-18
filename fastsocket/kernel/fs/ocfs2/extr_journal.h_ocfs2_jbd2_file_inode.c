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
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int /*<<< orphan*/  ip_jinode; } ;

/* Variables and functions */
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int jbd2_journal_file_inode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ocfs2_jbd2_file_inode(handle_t *handle, struct inode *inode)
{
	return jbd2_journal_file_inode(handle, &OCFS2_I(inode)->ip_jinode);
}
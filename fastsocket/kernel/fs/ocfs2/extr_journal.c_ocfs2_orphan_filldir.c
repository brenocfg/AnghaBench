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
typedef  int /*<<< orphan*/  u64 ;
struct ocfs2_orphan_filldir_priv {struct inode* head; int /*<<< orphan*/  osb; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {struct inode* ip_next_orphan; scalar_t__ ip_blkno; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_FI_FLAG_ORPHAN_RECOVERY ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 struct inode* ocfs2_iget (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,int) ; 

__attribute__((used)) static int ocfs2_orphan_filldir(void *priv, const char *name, int name_len,
				loff_t pos, u64 ino, unsigned type)
{
	struct ocfs2_orphan_filldir_priv *p = priv;
	struct inode *iter;

	if (name_len == 1 && !strncmp(".", name, 1))
		return 0;
	if (name_len == 2 && !strncmp("..", name, 2))
		return 0;

	/* Skip bad inodes so that recovery can continue */
	iter = ocfs2_iget(p->osb, ino,
			  OCFS2_FI_FLAG_ORPHAN_RECOVERY, 0);
	if (IS_ERR(iter))
		return 0;

	mlog(0, "queue orphan %llu\n",
	     (unsigned long long)OCFS2_I(iter)->ip_blkno);
	/* No locking is required for the next_orphan queue as there
	 * is only ever a single process doing orphan recovery. */
	OCFS2_I(iter)->ip_next_orphan = p->head;
	p->head = iter;

	return 0;
}
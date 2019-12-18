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
struct inode_security_struct {int /*<<< orphan*/  task_sid; int /*<<< orphan*/  sclass; int /*<<< orphan*/  sid; struct inode* inode; int /*<<< orphan*/  list; int /*<<< orphan*/  lock; } ;
struct inode {struct inode_security_struct* i_security; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SECCLASS_FILE ; 
 int /*<<< orphan*/  SECINITSID_UNLABELED ; 
 int /*<<< orphan*/  current_sid () ; 
 struct inode_security_struct* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sel_inode_cache ; 

__attribute__((used)) static int inode_alloc_security(struct inode *inode)
{
	struct inode_security_struct *isec;
	u32 sid = current_sid();

	isec = kmem_cache_zalloc(sel_inode_cache, GFP_NOFS);
	if (!isec)
		return -ENOMEM;

	mutex_init(&isec->lock);
	INIT_LIST_HEAD(&isec->list);
	isec->inode = inode;
	isec->sid = SECINITSID_UNLABELED;
	isec->sclass = SECCLASS_FILE;
	isec->task_sid = sid;
	inode->i_security = isec;

	return 0;
}
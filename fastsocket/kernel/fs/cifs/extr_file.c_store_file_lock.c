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
struct cifsLockInfo {int /*<<< orphan*/  llist; int /*<<< orphan*/  type; void* length; void* offset; } ;
struct cifsFileInfo {int /*<<< orphan*/  lock_mutex; int /*<<< orphan*/  llist; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  void* __u64 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct cifsLockInfo* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int store_file_lock(struct cifsFileInfo *fid, __u64 len,
				__u64 offset, __u8 lockType)
{
	struct cifsLockInfo *li =
		kmalloc(sizeof(struct cifsLockInfo), GFP_KERNEL);
	if (li == NULL)
		return -ENOMEM;
	li->offset = offset;
	li->length = len;
	li->type = lockType;
	mutex_lock(&fid->lock_mutex);
	list_add(&li->llist, &fid->llist);
	mutex_unlock(&fid->lock_mutex);
	return 0;
}
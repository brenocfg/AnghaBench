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
typedef  void* u64 ;
struct list_head {int dummy; } ;
struct btrfs_key {int dummy; } ;
struct __prelim_ref {int level; int count; int /*<<< orphan*/  list; void* wanted_disk_byte; void* parent; int /*<<< orphan*/ * inode_list; struct btrfs_key key_for_search; void* root_id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct __prelim_ref* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  memset (struct btrfs_key*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __add_prelim_ref(struct list_head *head, u64 root_id,
			    struct btrfs_key *key, int level,
			    u64 parent, u64 wanted_disk_byte, int count)
{
	struct __prelim_ref *ref;

	/* in case we're adding delayed refs, we're holding the refs spinlock */
	ref = kmalloc(sizeof(*ref), GFP_ATOMIC);
	if (!ref)
		return -ENOMEM;

	ref->root_id = root_id;
	if (key)
		ref->key_for_search = *key;
	else
		memset(&ref->key_for_search, 0, sizeof(ref->key_for_search));

	ref->inode_list = NULL;
	ref->level = level;
	ref->count = count;
	ref->parent = parent;
	ref->wanted_disk_byte = wanted_disk_byte;
	list_add_tail(&ref->list, head);

	return 0;
}
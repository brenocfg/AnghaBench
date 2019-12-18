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
struct mnt_namespace {scalar_t__ event; int /*<<< orphan*/  poll; int /*<<< orphan*/  list; int /*<<< orphan*/ * root; int /*<<< orphan*/  count; int /*<<< orphan*/  seq; int /*<<< orphan*/  proc_inum; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct mnt_namespace* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mnt_namespace*) ; 
 struct mnt_namespace* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mnt_ns_seq ; 
 int proc_alloc_inum (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mnt_namespace *alloc_mnt_ns(void)
{
	struct mnt_namespace *new_ns;
	int ret;

	new_ns = kmalloc(sizeof(struct mnt_namespace), GFP_KERNEL);
	if (!new_ns)
		return ERR_PTR(-ENOMEM);
	ret = proc_alloc_inum(&new_ns->proc_inum);
	if (ret) {
		kfree(new_ns);
		return ERR_PTR(ret);
	}
	new_ns->seq = atomic64_add_return(1, &mnt_ns_seq);
	atomic_set(&new_ns->count, 1);
	new_ns->root = NULL;
	INIT_LIST_HEAD(&new_ns->list);
	init_waitqueue_head(&new_ns->poll);
	new_ns->event = 0;
	return new_ns;
}
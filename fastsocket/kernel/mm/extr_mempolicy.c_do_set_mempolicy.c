#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;
struct TYPE_5__ {int /*<<< orphan*/  nodes; } ;
struct mempolicy {scalar_t__ mode; TYPE_1__ v; } ;
typedef  int /*<<< orphan*/  nodemask_t ;
struct TYPE_6__ {int /*<<< orphan*/  il_next; struct mempolicy* mempolicy; struct mm_struct* mm; } ;

/* Variables and functions */
 long ENOMEM ; 
 scalar_t__ IS_ERR (struct mempolicy*) ; 
 scalar_t__ MPOL_INTERLEAVE ; 
 int /*<<< orphan*/  NODEMASK_SCRATCH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NODEMASK_SCRATCH_FREE (int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct mempolicy*) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  first_node (int /*<<< orphan*/ ) ; 
 struct mempolicy* mpol_new (unsigned short,unsigned short,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpol_put (struct mempolicy*) ; 
 int mpol_set_nodemask (struct mempolicy*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpol_set_task_struct_flag () ; 
 scalar_t__ nodes_weight (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scratch ; 
 int /*<<< orphan*/  task_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  task_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long do_set_mempolicy(unsigned short mode, unsigned short flags,
			     nodemask_t *nodes)
{
	struct mempolicy *new, *old;
	struct mm_struct *mm = current->mm;
	NODEMASK_SCRATCH(scratch);
	int ret;

	if (!scratch)
		return -ENOMEM;

	new = mpol_new(mode, flags, nodes);
	if (IS_ERR(new)) {
		ret = PTR_ERR(new);
		goto out;
	}
	/*
	 * prevent changing our mempolicy while show_numa_maps()
	 * is using it.
	 * Note:  do_set_mempolicy() can be called at init time
	 * with no 'mm'.
	 */
	if (mm)
		down_write(&mm->mmap_sem);
	task_lock(current);
	ret = mpol_set_nodemask(new, nodes, scratch);
	if (ret) {
		task_unlock(current);
		if (mm)
			up_write(&mm->mmap_sem);
		mpol_put(new);
		goto out;
	}
	old = current->mempolicy;
	current->mempolicy = new;
	mpol_set_task_struct_flag();
	if (new && new->mode == MPOL_INTERLEAVE &&
	    nodes_weight(new->v.nodes))
		current->il_next = first_node(new->v.nodes);
	task_unlock(current);
	if (mm)
		up_write(&mm->mmap_sem);

	mpol_put(old);
	ret = 0;
out:
	NODEMASK_SCRATCH_FREE(scratch);
	return ret;
}
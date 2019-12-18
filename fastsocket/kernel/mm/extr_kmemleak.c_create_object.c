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
struct prio_tree_node {unsigned long start; unsigned long last; } ;
struct kmemleak_object {int flags; unsigned long pointer; size_t size; int min_count; int count; int /*<<< orphan*/  object_list; int /*<<< orphan*/  lock; struct prio_tree_node tree_node; int /*<<< orphan*/  trace; int /*<<< orphan*/  trace_len; int /*<<< orphan*/  comm; scalar_t__ pid; int /*<<< orphan*/  jiffies; int /*<<< orphan*/  use_count; int /*<<< orphan*/  area_list; int /*<<< orphan*/  gray_list; } ;
typedef  int gfp_t ;
struct TYPE_2__ {char* comm; scalar_t__ pid; } ;

/* Variables and functions */
 int GFP_KMEMLEAK_MASK ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_PRIO_TREE_NODE (struct prio_tree_node*) ; 
 int OBJECT_ALLOCATED ; 
 int OBJECT_NEW ; 
 int /*<<< orphan*/  __save_stack_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  dump_object_info (struct kmemleak_object*) ; 
 scalar_t__ in_irq () ; 
 scalar_t__ in_softirq () ; 
 int /*<<< orphan*/  jiffies ; 
 struct kmemleak_object* kmem_cache_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kmemleak_lock ; 
 int /*<<< orphan*/  kmemleak_stop (char*,...) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct kmemleak_object* lookup_object (unsigned long,int) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  max_addr ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  min_addr ; 
 int /*<<< orphan*/  object_cache ; 
 int /*<<< orphan*/  object_list ; 
 int /*<<< orphan*/  object_tree_root ; 
 struct prio_tree_node* prio_tree_insert (int /*<<< orphan*/ *,struct prio_tree_node*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct kmemleak_object *create_object(unsigned long ptr, size_t size,
					     int min_count, gfp_t gfp)
{
	unsigned long flags;
	struct kmemleak_object *object;
	struct prio_tree_node *node;

	object = kmem_cache_alloc(object_cache, gfp & GFP_KMEMLEAK_MASK);
	if (!object) {
		kmemleak_stop("Cannot allocate a kmemleak_object structure\n");
		return NULL;
	}

	INIT_LIST_HEAD(&object->object_list);
	INIT_LIST_HEAD(&object->gray_list);
	INIT_HLIST_HEAD(&object->area_list);
	spin_lock_init(&object->lock);
	atomic_set(&object->use_count, 1);
	object->flags = OBJECT_ALLOCATED | OBJECT_NEW;
	object->pointer = ptr;
	object->size = size;
	object->min_count = min_count;
	object->count = -1;			/* no color initially */
	object->jiffies = jiffies;

	/* task information */
	if (in_irq()) {
		object->pid = 0;
		strncpy(object->comm, "hardirq", sizeof(object->comm));
	} else if (in_softirq()) {
		object->pid = 0;
		strncpy(object->comm, "softirq", sizeof(object->comm));
	} else {
		object->pid = current->pid;
		/*
		 * There is a small chance of a race with set_task_comm(),
		 * however using get_task_comm() here may cause locking
		 * dependency issues with current->alloc_lock. In the worst
		 * case, the command line is not correct.
		 */
		strncpy(object->comm, current->comm, sizeof(object->comm));
	}

	/* kernel backtrace */
	object->trace_len = __save_stack_trace(object->trace);

	INIT_PRIO_TREE_NODE(&object->tree_node);
	object->tree_node.start = ptr;
	object->tree_node.last = ptr + size - 1;

	write_lock_irqsave(&kmemleak_lock, flags);

	min_addr = min(min_addr, ptr);
	max_addr = max(max_addr, ptr + size);
	node = prio_tree_insert(&object_tree_root, &object->tree_node);
	/*
	 * The code calling the kernel does not yet have the pointer to the
	 * memory block to be able to free it.  However, we still hold the
	 * kmemleak_lock here in case parts of the kernel started freeing
	 * random memory blocks.
	 */
	if (node != &object->tree_node) {
		kmemleak_stop("Cannot insert 0x%lx into the object search tree "
			      "(already existing)\n", ptr);
		object = lookup_object(ptr, 1);
		spin_lock(&object->lock);
		dump_object_info(object);
		spin_unlock(&object->lock);

		goto out;
	}
	list_add_tail_rcu(&object->object_list, &object_list);
out:
	write_unlock_irqrestore(&kmemleak_lock, flags);
	return object;
}
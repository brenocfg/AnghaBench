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
struct pid_namespace {int level; TYPE_1__* pidmap; int /*<<< orphan*/  proc_work; int /*<<< orphan*/  parent; int /*<<< orphan*/  kref; int /*<<< orphan*/  proc_inum; int /*<<< orphan*/ * pid_cachep; } ;
struct TYPE_2__ {int /*<<< orphan*/  page; int /*<<< orphan*/  nr_free; } ;

/* Variables and functions */
 scalar_t__ BITS_PER_PAGE ; 
 int ENOMEM ; 
 struct pid_namespace* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PIDMAP_ENTRIES ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * create_pid_cachep (unsigned int) ; 
 int /*<<< orphan*/  get_pid_ns (struct pid_namespace*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct pid_namespace*) ; 
 struct pid_namespace* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pid_ns_cachep ; 
 int proc_alloc_inum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_cleanup_work ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pid_namespace *create_pid_namespace(struct pid_namespace *parent_pid_ns)
{
	struct pid_namespace *ns;
	unsigned int level = parent_pid_ns->level + 1;
	int i, err = -ENOMEM;

	ns = kmem_cache_zalloc(pid_ns_cachep, GFP_KERNEL);
	if (ns == NULL)
		goto out;

	ns->pidmap[0].page = kzalloc(PAGE_SIZE, GFP_KERNEL);
	if (!ns->pidmap[0].page)
		goto out_free;

	ns->pid_cachep = create_pid_cachep(level + 1);
	if (ns->pid_cachep == NULL)
		goto out_free_map;

	err = proc_alloc_inum(&ns->proc_inum);
	if (err)
		goto out_free_map;

	kref_init(&ns->kref);
	ns->level = level;
	ns->parent = get_pid_ns(parent_pid_ns);
	INIT_WORK(&ns->proc_work, proc_cleanup_work);

	set_bit(0, ns->pidmap[0].page);
	atomic_set(&ns->pidmap[0].nr_free, BITS_PER_PAGE - 1);

	for (i = 1; i < PIDMAP_ENTRIES; i++)
		atomic_set(&ns->pidmap[i].nr_free, BITS_PER_PAGE);

	return ns;

out_free_map:
	kfree(ns->pidmap[0].page);
out_free:
	kmem_cache_free(pid_ns_cachep, ns);
out:
	return ERR_PTR(err);
}
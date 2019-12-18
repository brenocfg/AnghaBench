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
struct bsg_device {scalar_t__ queued_cmds; scalar_t__ max_queue; int /*<<< orphan*/  lock; int /*<<< orphan*/  name; } ;
struct bsg_command {int /*<<< orphan*/  list; struct bsg_device* bd; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct bsg_command* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bsg_cmd_cachep ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,struct bsg_command*) ; 
 struct bsg_command* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct bsg_command *bsg_alloc_command(struct bsg_device *bd)
{
	struct bsg_command *bc = ERR_PTR(-EINVAL);

	spin_lock_irq(&bd->lock);

	if (bd->queued_cmds >= bd->max_queue)
		goto out;

	bd->queued_cmds++;
	spin_unlock_irq(&bd->lock);

	bc = kmem_cache_zalloc(bsg_cmd_cachep, GFP_KERNEL);
	if (unlikely(!bc)) {
		spin_lock_irq(&bd->lock);
		bd->queued_cmds--;
		bc = ERR_PTR(-ENOMEM);
		goto out;
	}

	bc->bd = bd;
	INIT_LIST_HEAD(&bc->list);
	dprintk("%s: returning free cmd %p\n", bd->name, bc);
	return bc;
out:
	spin_unlock_irq(&bd->lock);
	return bc;
}
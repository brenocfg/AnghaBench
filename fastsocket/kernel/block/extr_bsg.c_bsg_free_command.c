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
struct bsg_device {int /*<<< orphan*/  wq_free; int /*<<< orphan*/  lock; int /*<<< orphan*/  queued_cmds; } ;
struct bsg_command {struct bsg_device* bd; } ;

/* Variables and functions */
 int /*<<< orphan*/  bsg_cmd_cachep ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct bsg_command*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bsg_free_command(struct bsg_command *bc)
{
	struct bsg_device *bd = bc->bd;
	unsigned long flags;

	kmem_cache_free(bsg_cmd_cachep, bc);

	spin_lock_irqsave(&bd->lock, flags);
	bd->queued_cmds--;
	spin_unlock_irqrestore(&bd->lock, flags);

	wake_up(&bd->wq_free);
}
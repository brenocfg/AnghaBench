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
struct i1480u_tx {int /*<<< orphan*/  list_node; } ;
struct i1480u {int /*<<< orphan*/  tx_list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  i1480u_tx_free (struct i1480u_tx*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static
void i1480u_tx_destroy(struct i1480u *i1480u, struct i1480u_tx *wtx)
{
	unsigned long flags;
	spin_lock_irqsave(&i1480u->tx_list_lock, flags);	/* not active any more */
	list_del(&wtx->list_node);
	i1480u_tx_free(wtx);
	spin_unlock_irqrestore(&i1480u->tx_list_lock, flags);
}
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
struct lbs_private {int /*<<< orphan*/  driver_lock; } ;
struct cmd_ctrl_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __lbs_cleanup_and_insert_cmd (struct lbs_private*,struct cmd_ctrl_node*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void lbs_cleanup_and_insert_cmd(struct lbs_private *priv,
	struct cmd_ctrl_node *ptempcmd)
{
	unsigned long flags;

	spin_lock_irqsave(&priv->driver_lock, flags);
	__lbs_cleanup_and_insert_cmd(priv, ptempcmd);
	spin_unlock_irqrestore(&priv->driver_lock, flags);
}
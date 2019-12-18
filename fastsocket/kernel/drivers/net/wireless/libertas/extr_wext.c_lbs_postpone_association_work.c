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
struct lbs_private {int /*<<< orphan*/  assoc_work; int /*<<< orphan*/  work_thread; scalar_t__ surpriseremoved; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void lbs_postpone_association_work(struct lbs_private *priv)
{
	if (priv->surpriseremoved)
		return;
	cancel_delayed_work(&priv->assoc_work);
	queue_delayed_work(priv->work_thread, &priv->assoc_work, HZ / 2);
}
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
struct iss_net_private {int /*<<< orphan*/  lock; scalar_t__ timer_val; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  iss_net_poll () ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iss_net_timer(unsigned long priv)
{
	struct iss_net_private* lp = (struct iss_net_private*) priv;

	spin_lock(&lp->lock);

	iss_net_poll();

	mod_timer(&lp->timer, jiffies + lp->timer_val);

	spin_unlock(&lp->lock);
}
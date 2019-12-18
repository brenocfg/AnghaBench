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
struct async_domain {int dummy; } ;
typedef  int /*<<< orphan*/  async_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  __lowest_in_progress (struct async_domain*) ; 
 int /*<<< orphan*/  async_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static async_cookie_t  lowest_in_progress(struct async_domain *running)
{
	unsigned long flags;
	async_cookie_t ret;

	spin_lock_irqsave(&async_lock, flags);
	ret = __lowest_in_progress(running);
	spin_unlock_irqrestore(&async_lock, flags);
	return ret;
}
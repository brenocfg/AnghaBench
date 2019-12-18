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
struct c4iw_ep {int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_work ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timeout_list ; 
 int /*<<< orphan*/  timeout_lock ; 
 int /*<<< orphan*/  workq ; 

__attribute__((used)) static void ep_timeout(unsigned long arg)
{
	struct c4iw_ep *ep = (struct c4iw_ep *)arg;

	spin_lock(&timeout_lock);
	list_add_tail(&ep->entry, &timeout_list);
	spin_unlock(&timeout_lock);
	queue_work(workq, &skb_work);
}
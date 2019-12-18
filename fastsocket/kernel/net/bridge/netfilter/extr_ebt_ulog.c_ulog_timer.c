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
struct TYPE_2__ {int /*<<< orphan*/  lock; scalar_t__ skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 TYPE_1__* ulog_buffers ; 
 int /*<<< orphan*/  ulog_send (unsigned long) ; 

__attribute__((used)) static void ulog_timer(unsigned long data)
{
	spin_lock_bh(&ulog_buffers[data].lock);
	if (ulog_buffers[data].skb)
		ulog_send(data);
	spin_unlock_bh(&ulog_buffers[data].lock);
}
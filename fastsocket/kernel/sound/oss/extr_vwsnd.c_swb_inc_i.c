#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ vwsnd_port_t ;

/* Variables and functions */
 unsigned int __swb_inc_i (TYPE_1__*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static __inline__ unsigned int swb_inc_i(vwsnd_port_t *port, int inc)
{
	unsigned long flags;
	unsigned int ret;

	spin_lock_irqsave(&port->lock, flags);
	{
		ret = __swb_inc_i(port, inc);
	}
	spin_unlock_irqrestore(&port->lock, flags);
	return ret;
}
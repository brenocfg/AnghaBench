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
struct ib_device {int dummy; } ;
struct ib_agent_port_private {int dummy; } ;

/* Variables and functions */
 struct ib_agent_port_private* __ib_get_agent_port (struct ib_device*,int) ; 
 int /*<<< orphan*/  ib_agent_port_list_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct ib_agent_port_private *
ib_get_agent_port(struct ib_device *device, int port_num)
{
	struct ib_agent_port_private *entry;
	unsigned long flags;

	spin_lock_irqsave(&ib_agent_port_list_lock, flags);
	entry = __ib_get_agent_port(device, port_num);
	spin_unlock_irqrestore(&ib_agent_port_list_lock, flags);
	return entry;
}
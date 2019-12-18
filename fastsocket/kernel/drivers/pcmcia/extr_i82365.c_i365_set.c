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
typedef  size_t u_short ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_2__ {unsigned int ioaddr; int /*<<< orphan*/  psock; } ;

/* Variables and functions */
 int /*<<< orphan*/  I365_REG (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  bus_lock ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_1__* socket ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void i365_set(u_short sock, u_short reg, u_char data)
{
    unsigned long flags;
    spin_lock_irqsave(&bus_lock,flags);
    {
	unsigned int port = socket[sock].ioaddr;
	u_char val = I365_REG(socket[sock].psock, reg);
	outb(val, port); outb(data, port+1);
	spin_unlock_irqrestore(&bus_lock,flags);
    }
}
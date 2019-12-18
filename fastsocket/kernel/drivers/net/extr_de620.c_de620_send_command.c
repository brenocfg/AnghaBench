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
struct net_device {int dummy; } ;
typedef  scalar_t__ byte ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND_PORT ; 
 scalar_t__ CS0 ; 
 int /*<<< orphan*/  DATA_PORT ; 
 scalar_t__ NIC_Cmd ; 
 scalar_t__ W_DUMMY ; 
 int /*<<< orphan*/  de620_ready (struct net_device*) ; 
 int /*<<< orphan*/  outb (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
de620_send_command(struct net_device *dev, byte cmd)
{
	de620_ready(dev);
	if (cmd == W_DUMMY)
		outb(NIC_Cmd, COMMAND_PORT);

	outb(cmd, DATA_PORT);

	outb(NIC_Cmd ^ CS0, COMMAND_PORT);
	de620_ready(dev);
	outb(NIC_Cmd, COMMAND_PORT);
}
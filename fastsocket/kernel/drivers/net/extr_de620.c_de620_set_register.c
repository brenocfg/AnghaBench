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
typedef  int byte ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND_PORT ; 
 int CS0 ; 
 int /*<<< orphan*/  DATA_PORT ; 
 int NIC_Cmd ; 
 int /*<<< orphan*/  de620_put_byte (struct net_device*,int) ; 
 int /*<<< orphan*/  de620_ready (struct net_device*) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
de620_set_register(struct net_device *dev, byte reg, byte value)
{
	de620_ready(dev);
	outb(reg, DATA_PORT);
	outb(NIC_Cmd ^ CS0, COMMAND_PORT);

	de620_put_byte(dev, value);
}
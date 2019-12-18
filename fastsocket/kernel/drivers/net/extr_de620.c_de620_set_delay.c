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

/* Variables and functions */
 int /*<<< orphan*/  COMMAND_PORT ; 
 int CS0 ; 
 int /*<<< orphan*/  DATA_PORT ; 
 int NIC_Cmd ; 
 int READ_DELAY ; 
 int WRITE_DELAY ; 
 int W_DFR ; 
 int /*<<< orphan*/  de620_flip_ds (struct net_device*) ; 
 int /*<<< orphan*/  de620_ready (struct net_device*) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
de620_set_delay(struct net_device *dev)
{
	de620_ready(dev);
	outb(W_DFR, DATA_PORT);
	outb(NIC_Cmd ^ CS0, COMMAND_PORT);

	de620_ready(dev);
#ifdef LOWSPEED
	outb(WRITE_DELAY, DATA_PORT);
#else
	outb(0, DATA_PORT);
#endif
	de620_flip_ds(dev);

	de620_ready(dev);
#ifdef LOWSPEED
	outb(READ_DELAY, DATA_PORT);
#else
	outb(0, DATA_PORT);
#endif
	de620_flip_ds(dev);
}
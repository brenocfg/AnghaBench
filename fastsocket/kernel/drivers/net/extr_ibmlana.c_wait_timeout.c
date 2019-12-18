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
typedef  int u16 ;
struct net_device {scalar_t__ base_addr; } ;

/* Variables and functions */
 int inw (scalar_t__) ; 
 int jiffies ; 
 scalar_t__ time_before (int,unsigned long) ; 

__attribute__((used)) static int wait_timeout(struct net_device *dev, int regoffs, u16 mask,
			u16 value, int timeout)
{
	unsigned long fin = jiffies + timeout;

	while (time_before(jiffies,fin))
		if ((inw(dev->base_addr + regoffs) & mask) == value)
			return 1;

	return 0;
}
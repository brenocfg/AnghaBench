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
struct net_device {scalar_t__ base_addr; } ;

/* Variables and functions */
 unsigned short inw (scalar_t__) ; 

__attribute__((used)) static inline unsigned short scb_rdcmd(struct net_device *dev)
{
	return inw(dev->base_addr + 0xc00a);
}
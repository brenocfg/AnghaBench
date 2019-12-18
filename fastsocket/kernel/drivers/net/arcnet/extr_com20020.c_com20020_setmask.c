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
typedef  int /*<<< orphan*/  u_int ;
struct net_device {int /*<<< orphan*/  base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AINTMASK (int) ; 
 int /*<<< orphan*/  BUGMSG (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D_DURING ; 

__attribute__((used)) static void com20020_setmask(struct net_device *dev, int mask)
{
	u_int ioaddr = dev->base_addr;
	BUGMSG(D_DURING, "Setting mask to %x at %x\n",mask,ioaddr);
	AINTMASK(mask);
}
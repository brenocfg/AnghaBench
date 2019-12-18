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
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int b43_phy_initn (struct b43_wldev*) ; 

__attribute__((used)) static int b43_nphy_op_init(struct b43_wldev *dev)
{
	return b43_phy_initn(dev);
}
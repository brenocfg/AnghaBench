#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_3__ {struct net_device* dev; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  HFA384X_OUTB (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SANDISK_HCR_OFF ; 
 int /*<<< orphan*/  SANDISK_WLAN_ACTIVATION_OFF ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void sandisk_write_hcr(local_info_t *local, int hcr)
{
	struct net_device *dev = local->dev;
	int i;

	HFA384X_OUTB(0x80, SANDISK_WLAN_ACTIVATION_OFF);
	udelay(50);
	for (i = 0; i < 10; i++) {
		HFA384X_OUTB(hcr, SANDISK_HCR_OFF);
	}
	udelay(55);
	HFA384X_OUTB(0x45, SANDISK_WLAN_ACTIVATION_OFF);
}
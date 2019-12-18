#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct b43legacy_wldev {TYPE_3__* dev; } ;
struct TYPE_6__ {TYPE_2__* bus; } ;
struct TYPE_4__ {scalar_t__ vendor; } ;
struct TYPE_5__ {TYPE_1__ boardinfo; } ;

/* Variables and functions */
 scalar_t__ PCI_VENDOR_ID_BROADCOM ; 

__attribute__((used)) static inline
bool is_bcm_board_vendor(struct b43legacy_wldev *dev)
{
	return  (dev->dev->bus->boardinfo.vendor == PCI_VENDOR_ID_BROADCOM);
}
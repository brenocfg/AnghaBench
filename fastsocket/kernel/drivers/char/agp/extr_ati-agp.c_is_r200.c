#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* dev; } ;
struct TYPE_3__ {scalar_t__ device; } ;

/* Variables and functions */
 scalar_t__ PCI_DEVICE_ID_ATI_RS100 ; 
 scalar_t__ PCI_DEVICE_ID_ATI_RS200 ; 
 scalar_t__ PCI_DEVICE_ID_ATI_RS200_B ; 
 scalar_t__ PCI_DEVICE_ID_ATI_RS250 ; 
 TYPE_2__* agp_bridge ; 

__attribute__((used)) static int is_r200(void)
{
	if ((agp_bridge->dev->device == PCI_DEVICE_ID_ATI_RS100) ||
	    (agp_bridge->dev->device == PCI_DEVICE_ID_ATI_RS200) ||
	    (agp_bridge->dev->device == PCI_DEVICE_ID_ATI_RS200_B) ||
	    (agp_bridge->dev->device == PCI_DEVICE_ID_ATI_RS250))
		return 1;
	return 0;
}
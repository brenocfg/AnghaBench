#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ idVendor; scalar_t__ idProduct; TYPE_2__* configurations; } ;
typedef  TYPE_3__ usb_devdesc ;
struct TYPE_6__ {TYPE_1__* interfaces; } ;
struct TYPE_5__ {scalar_t__ bInterfaceSubClass; scalar_t__ endpoints; } ;

/* Variables and functions */
 scalar_t__ PID_RETRODE ; 
 scalar_t__ VID_RETRODE ; 

__attribute__((used)) static bool isRetrodeGamepad(usb_devdesc devdesc)
{
    if (devdesc.idVendor != VID_RETRODE || devdesc.idProduct != PID_RETRODE)
        return false;
    if (devdesc.configurations)
        if (devdesc.configurations->interfaces)
            if (devdesc.configurations->interfaces->endpoints)
                return devdesc.configurations->interfaces->bInterfaceSubClass == 0;
    return false;
}
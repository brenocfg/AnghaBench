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
struct usb_bus {struct mon_bus* mon_bus; } ;
struct urb {int dummy; } ;
struct mon_bus {int dummy; } ;

/* Variables and functions */
 struct mon_bus mon_bus0 ; 
 int /*<<< orphan*/  mon_bus_complete (struct mon_bus*,struct urb*,int) ; 

__attribute__((used)) static void mon_complete(struct usb_bus *ubus, struct urb *urb, int status)
{
	struct mon_bus *mbus;

	if ((mbus = ubus->mon_bus) != NULL)
		mon_bus_complete(mbus, urb, status);
	mon_bus_complete(&mon_bus0, urb, status);
}
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
struct usb_ep {scalar_t__ name; } ;

/* Variables and functions */
 int EINVAL ; 
 int dummy_set_halt_and_wedge (struct usb_ep*,int,int) ; 
 scalar_t__ ep0name ; 

__attribute__((used)) static int dummy_set_wedge(struct usb_ep *_ep)
{
	if (!_ep || _ep->name == ep0name)
		return -EINVAL;
	return dummy_set_halt_and_wedge(_ep, 1, 1);
}
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
struct oxu_hcd {int dummy; } ;

/* Variables and functions */
 int USB_PORT_FEAT_HIGHSPEED ; 
 int USB_PORT_FEAT_LOWSPEED ; 

__attribute__((used)) static inline unsigned int oxu_port_speed(struct oxu_hcd *oxu,
						unsigned int portsc)
{
	switch ((portsc >> 26) & 3) {
	case 0:
		return 0;
	case 1:
		return 1 << USB_PORT_FEAT_LOWSPEED;
	case 2:
	default:
		return 1 << USB_PORT_FEAT_HIGHSPEED;
	}
}
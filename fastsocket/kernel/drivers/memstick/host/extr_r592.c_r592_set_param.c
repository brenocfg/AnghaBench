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
struct r592_device {int dummy; } ;
struct memstick_host {int dummy; } ;
typedef  enum memstick_param { ____Placeholder_memstick_param } memstick_param ;

/* Variables and functions */
 int EINVAL ; 
#define  MEMSTICK_INTERFACE 133 
#define  MEMSTICK_PAR4 132 
#define  MEMSTICK_POWER 131 
#define  MEMSTICK_POWER_OFF 130 
#define  MEMSTICK_POWER_ON 129 
#define  MEMSTICK_SERIAL 128 
 struct r592_device* memstick_priv (struct memstick_host*) ; 
 int r592_enable_device (struct r592_device*,int) ; 
 int r592_set_mode (struct r592_device*,int) ; 

__attribute__((used)) static int r592_set_param(struct memstick_host *host,
			enum memstick_param param, int value)
{
	struct r592_device *dev = memstick_priv(host);

	switch (param) {
	case MEMSTICK_POWER:
		switch (value) {
		case MEMSTICK_POWER_ON:
			return r592_enable_device(dev, true);
		case MEMSTICK_POWER_OFF:
			return r592_enable_device(dev, false);
		default:
			return -EINVAL;
		}
	case MEMSTICK_INTERFACE:
		switch (value) {
		case MEMSTICK_SERIAL:
			return r592_set_mode(dev, 0);
		case MEMSTICK_PAR4:
			return r592_set_mode(dev, 1);
		default:
			return -EINVAL;
		}
	default:
		return -EINVAL;
	}
}
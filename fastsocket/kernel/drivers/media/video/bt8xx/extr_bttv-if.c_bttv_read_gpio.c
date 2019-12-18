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
struct bttv {scalar_t__ shutdown; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 unsigned int bttv_num ; 
 struct bttv** bttvs ; 
 unsigned long gpio_read () ; 

int bttv_read_gpio(unsigned int card, unsigned long *data)
{
	struct bttv *btv;

	if (card >= bttv_num) {
		return -EINVAL;
	}

	btv = bttvs[card];
	if (!btv)
		return -ENODEV;

	if(btv->shutdown) {
		return -ENODEV;
	}

/* prior setting BT848_GPIO_REG_INP is (probably) not needed
   because we set direct input on init */
	*data = gpio_read();
	return 0;
}
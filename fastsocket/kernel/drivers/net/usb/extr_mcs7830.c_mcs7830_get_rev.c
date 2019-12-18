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
typedef  int /*<<< orphan*/  u8 ;
struct usbnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIF_REG_22 ; 
 int mcs7830_get_reg (struct usbnet*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mcs7830_get_rev(struct usbnet *dev)
{
	u8 dummy[2];
	int ret;
	ret = mcs7830_get_reg(dev, HIF_REG_22, 2, dummy);
	if (ret > 0)
		return 2; /* Rev C or later */
	return 1; /* earlier revision */
}
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
typedef  scalar_t__ u32 ;
struct sisusb_usb_data {scalar_t__ vrambase; } ;

/* Variables and functions */
 int READL (scalar_t__,scalar_t__*) ; 
 int WRITEL (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
sisusb_check_rbc(struct sisusb_usb_data *sisusb, int *iret, u32 inc, int testn)
{
	int ret = 0, i;
	u32 j, tmp;

	*iret = 0;

	for (i = 0, j = 0; i < testn; i++) {
		ret |= WRITEL(sisusb->vrambase + j, j);
		j += inc;
	}

	for (i = 0, j = 0; i < testn; i++) {
		ret |= READL(sisusb->vrambase + j, &tmp);
		if (tmp != j) return ret;
		j += inc;
	}

	*iret = 1;
	return ret;
}
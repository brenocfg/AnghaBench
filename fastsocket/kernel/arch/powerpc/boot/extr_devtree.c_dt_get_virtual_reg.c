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

/* Variables and functions */
 int /*<<< orphan*/  dt_xlate_reg (void*,int,unsigned long*,int /*<<< orphan*/ *) ; 
 int getprop (void*,char*,void**,int) ; 

int dt_get_virtual_reg(void *node, void **addr, int nres)
{
	unsigned long xaddr;
	int n;

	n = getprop(node, "virtual-reg", addr, nres * 4);
	if (n > 0)
		return n / 4;

	for (n = 0; n < nres; n++) {
		if (!dt_xlate_reg(node, n, &xaddr, NULL))
			break;

		addr[n] = (void *)xaddr;
	}

	return n;
}
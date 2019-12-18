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
struct otg_transceiver {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 struct otg_transceiver* xceiv ; 

int otg_set_transceiver(struct otg_transceiver *x)
{
	if (xceiv && x)
		return -EBUSY;
	xceiv = x;
	return 0;
}
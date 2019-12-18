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
 int /*<<< orphan*/  BUG () ; 
 int NI_GPCT0_SUBDEV ; 
 int NI_GPCT1_SUBDEV ; 

__attribute__((used)) static inline unsigned NI_GPCT_SUBDEV(unsigned counter_index)
{
	switch (counter_index) {
	case 0:
		return NI_GPCT0_SUBDEV;
		break;
	case 1:
		return NI_GPCT1_SUBDEV;
		break;
	default:
		break;
	}
	BUG();
	return NI_GPCT0_SUBDEV;
}
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
typedef  int /*<<< orphan*/  v ;
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 void* finddevice (char*) ; 
 scalar_t__ getprop (void*,char*,int /*<<< orphan*/ *,int) ; 

u8 mv64x60_is_coherent(void)
{
	u32 v;
	void *devp;

	devp = finddevice("/");
	if (devp == NULL)
		return 1; /* Assume coherency on */

	if (getprop(devp, "coherency-off", &v, sizeof(v)) < 0)
		return 1; /* Coherency on */
	else
		return 0;
}
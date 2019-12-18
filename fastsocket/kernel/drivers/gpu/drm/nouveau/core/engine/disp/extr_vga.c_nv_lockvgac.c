#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {int chipset; } ;

/* Variables and functions */
 TYPE_1__* nv_device (void*) ; 
 int nv_rd32 (void*,int) ; 
 int /*<<< orphan*/  nv_rdvgac (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nv_wrvgac (void*,int,int,int) ; 

bool
nv_lockvgac(void *obj, bool lock)
{
	bool locked = !nv_rdvgac(obj, 0, 0x1f);
	u8 data = lock ? 0x99 : 0x57;
	nv_wrvgac(obj, 0, 0x1f, data);
	if (nv_device(obj)->chipset == 0x11) {
		if (!(nv_rd32(obj, 0x001084) & 0x10000000))
			nv_wrvgac(obj, 1, 0x1f, data);
	}
	return locked;
}
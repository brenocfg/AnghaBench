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
struct TYPE_2__ {scalar_t__ card_type; int chipset; } ;

/* Variables and functions */
 scalar_t__ NV_50 ; 
 TYPE_1__* nv_device (void*) ; 
 int /*<<< orphan*/  nv_error (void*,char*) ; 
 int /*<<< orphan*/  nv_rdvgac (void*,int,int) ; 
 int /*<<< orphan*/  nv_wrvgac (void*,int /*<<< orphan*/ ,int,int) ; 

void
nv_wrvgaowner(void *obj, u8 select)
{
	if (nv_device(obj)->card_type < NV_50) {
		u8 owner = (select == 1) ? 3 : select;
		if (nv_device(obj)->chipset == 0x11) {
			/* workaround hw lockup bug */
			nv_rdvgac(obj, 0, 0x1f);
			nv_rdvgac(obj, 1, 0x1f);
		}

		nv_wrvgac(obj, 0, 0x44, owner);

		if (nv_device(obj)->chipset == 0x11) {
			nv_wrvgac(obj, 0, 0x2e, owner);
			nv_wrvgac(obj, 0, 0x2e, owner);
		}
	} else
		nv_error(obj, "wrvgaowner after nv4x\n");
}
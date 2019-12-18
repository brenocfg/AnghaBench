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
typedef  int u32 ;
struct nouveau_device {int chipset; } ;

/* Variables and functions */
 struct nouveau_device* nv_device (void*) ; 

__attribute__((used)) static inline u32
nvc0_graph_class(void *obj)
{
	struct nouveau_device *device = nv_device(obj);

	switch (device->chipset) {
	case 0xc0:
	case 0xc3:
	case 0xc4:
	case 0xce: /* guess, mmio trace shows only 0x9097 state */
	case 0xcf: /* guess, mmio trace shows only 0x9097 state */
		return 0x9097;
	case 0xc1:
		return 0x9197;
	case 0xc8:
	case 0xd9:
		return 0x9297;
	case 0xe4:
	case 0xe7:
	case 0xe6:
		return 0xa097;
	default:
		return 0;
	}
}
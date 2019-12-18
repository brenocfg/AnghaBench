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
struct pll_mapping {int dummy; } ;
struct nouveau_bios {int dummy; } ;
struct TYPE_2__ {int card_type; int chipset; } ;

/* Variables and functions */
#define  NV_04 133 
#define  NV_10 132 
#define  NV_20 131 
#define  NV_30 130 
#define  NV_40 129 
#define  NV_50 128 
 struct pll_mapping* nv04_pll_mapping ; 
 struct pll_mapping* nv40_pll_mapping ; 
 struct pll_mapping* nv50_pll_mapping ; 
 struct pll_mapping* nv84_pll_mapping ; 
 TYPE_1__* nv_device (struct nouveau_bios*) ; 

__attribute__((used)) static struct pll_mapping *
pll_map(struct nouveau_bios *bios)
{
	switch (nv_device(bios)->card_type) {
	case NV_04:
	case NV_10:
	case NV_20:
	case NV_30:
		return nv04_pll_mapping;
		break;
	case NV_40:
		return nv40_pll_mapping;
	case NV_50:
		if (nv_device(bios)->chipset == 0x50)
			return nv50_pll_mapping;
		else
		if (nv_device(bios)->chipset <  0xa3 ||
		    nv_device(bios)->chipset == 0xaa ||
		    nv_device(bios)->chipset == 0xac)
			return nv84_pll_mapping;
	default:
		return NULL;
	}
}
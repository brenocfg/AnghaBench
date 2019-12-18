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
struct wacom_wac {TYPE_1__* features; } ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
#define  BAMBOO_PT 152 
#define  CINTIQ 151 
#define  DTU 150 
#define  GRAPHIRE 149 
#define  INTUOS 148 
#define  INTUOS3 147 
#define  INTUOS3L 146 
#define  INTUOS3S 145 
#define  INTUOS4 144 
#define  INTUOS4L 143 
#define  INTUOS4S 142 
#define  INTUOS5 141 
#define  INTUOS5L 140 
#define  INTUOS5S 139 
#define  PENPARTNER 138 
#define  PL 137 
#define  PTU 136 
#define  TABLETPC 135 
#define  TABLETPC2FG 134 
#define  WACOM_21UX2 133 
#define  WACOM_22HD 132 
#define  WACOM_24HD 131 
#define  WACOM_BEE 130 
#define  WACOM_G4 129 
#define  WACOM_MO 128 
 int wacom_bpt_irq (struct wacom_wac*,void*) ; 
 int wacom_dtu_irq (struct wacom_wac*,void*) ; 
 int wacom_graphire_irq (struct wacom_wac*,void*) ; 
 int wacom_intuos_irq (struct wacom_wac*,void*) ; 
 int wacom_penpartner_irq (struct wacom_wac*,void*) ; 
 int wacom_pl_irq (struct wacom_wac*,void*) ; 
 int wacom_ptu_irq (struct wacom_wac*,void*) ; 
 int wacom_tpc_irq (struct wacom_wac*,void*) ; 

int wacom_wac_irq(struct wacom_wac *wacom_wac, void *wcombo)
{
	switch (wacom_wac->features->type) {
		case PENPARTNER:
			return wacom_penpartner_irq(wacom_wac, wcombo);

		case PL:
			return wacom_pl_irq(wacom_wac, wcombo);

		case WACOM_G4:
		case GRAPHIRE:
		case WACOM_MO:
			return wacom_graphire_irq(wacom_wac, wcombo);

		case PTU:
			return wacom_ptu_irq(wacom_wac, wcombo);

		case DTU:
			return wacom_dtu_irq(wacom_wac, wcombo);

		case INTUOS:
		case INTUOS3S:
		case INTUOS3:
		case INTUOS3L:
		case INTUOS4S:
		case INTUOS4:
		case INTUOS4L:
		case INTUOS5S:
		case INTUOS5:
		case INTUOS5L:
		case CINTIQ:
		case WACOM_BEE:
		case WACOM_21UX2:
		case WACOM_22HD:
		case WACOM_24HD:
			return wacom_intuos_irq(wacom_wac, wcombo);

		case TABLETPC:
		case TABLETPC2FG:
			return wacom_tpc_irq(wacom_wac, wcombo);
		case BAMBOO_PT:
			return wacom_bpt_irq(wacom_wac, wcombo);

		default:
			return 0;
	}
	return 0;
}
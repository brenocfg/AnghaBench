#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ad_type; TYPE_1__* nvram; } ;
struct TYPE_3__ {int* adapter_order; } ;
typedef  TYPE_1__ IPS_NVRAM_P5 ;

/* Variables and functions */
#define  IPS_ADTYPE_KIOWA 144 
#define  IPS_ADTYPE_NAVAJO 143 
#define  IPS_ADTYPE_SERVERAID 142 
#define  IPS_ADTYPE_SERVERAID2 141 
#define  IPS_ADTYPE_SERVERAID3 140 
#define  IPS_ADTYPE_SERVERAID3L 139 
#define  IPS_ADTYPE_SERVERAID4H 138 
#define  IPS_ADTYPE_SERVERAID4L 137 
#define  IPS_ADTYPE_SERVERAID4LX 136 
#define  IPS_ADTYPE_SERVERAID4M 135 
#define  IPS_ADTYPE_SERVERAID4MX 134 
#define  IPS_ADTYPE_SERVERAID5I1 133 
#define  IPS_ADTYPE_SERVERAID5I2 132 
#define  IPS_ADTYPE_SERVERAID6I 131 
#define  IPS_ADTYPE_SERVERAID6M 130 
#define  IPS_ADTYPE_SERVERAID7M 129 
#define  IPS_ADTYPE_SERVERAID7k 128 
 TYPE_2__** ips_ha ; 
 int ips_num_controllers ; 
 int /*<<< orphan*/  ips_shift_controllers (int,int) ; 

__attribute__((used)) static void
ips_order_controllers(void)
{
	int i, j, tmp, position = 0;
	IPS_NVRAM_P5 *nvram;
	if (!ips_ha[0])
		return;
	nvram = ips_ha[0]->nvram;

	if (nvram->adapter_order[0]) {
		for (i = 1; i <= nvram->adapter_order[0]; i++) {
			for (j = position; j < ips_num_controllers; j++) {
				switch (ips_ha[j]->ad_type) {
				case IPS_ADTYPE_SERVERAID6M:
				case IPS_ADTYPE_SERVERAID7M:
					if (nvram->adapter_order[i] == 'M') {
						ips_shift_controllers(position,
								      j);
						position++;
					}
					break;
				case IPS_ADTYPE_SERVERAID4L:
				case IPS_ADTYPE_SERVERAID4M:
				case IPS_ADTYPE_SERVERAID4MX:
				case IPS_ADTYPE_SERVERAID4LX:
					if (nvram->adapter_order[i] == 'N') {
						ips_shift_controllers(position,
								      j);
						position++;
					}
					break;
				case IPS_ADTYPE_SERVERAID6I:
				case IPS_ADTYPE_SERVERAID5I2:
				case IPS_ADTYPE_SERVERAID5I1:
				case IPS_ADTYPE_SERVERAID7k:
					if (nvram->adapter_order[i] == 'S') {
						ips_shift_controllers(position,
								      j);
						position++;
					}
					break;
				case IPS_ADTYPE_SERVERAID:
				case IPS_ADTYPE_SERVERAID2:
				case IPS_ADTYPE_NAVAJO:
				case IPS_ADTYPE_KIOWA:
				case IPS_ADTYPE_SERVERAID3L:
				case IPS_ADTYPE_SERVERAID3:
				case IPS_ADTYPE_SERVERAID4H:
					if (nvram->adapter_order[i] == 'A') {
						ips_shift_controllers(position,
								      j);
						position++;
					}
					break;
				default:
					break;
				}
			}
		}
		/* if adapter_order[0], then ordering is complete */
		return;
	}
	/* old bios, use older ordering */
	tmp = 0;
	for (i = position; i < ips_num_controllers; i++) {
		if (ips_ha[i]->ad_type == IPS_ADTYPE_SERVERAID5I2 ||
		    ips_ha[i]->ad_type == IPS_ADTYPE_SERVERAID5I1) {
			ips_shift_controllers(position, i);
			position++;
			tmp = 1;
		}
	}
	/* if there were no 5I cards, then don't do any extra ordering */
	if (!tmp)
		return;
	for (i = position; i < ips_num_controllers; i++) {
		if (ips_ha[i]->ad_type == IPS_ADTYPE_SERVERAID4L ||
		    ips_ha[i]->ad_type == IPS_ADTYPE_SERVERAID4M ||
		    ips_ha[i]->ad_type == IPS_ADTYPE_SERVERAID4LX ||
		    ips_ha[i]->ad_type == IPS_ADTYPE_SERVERAID4MX) {
			ips_shift_controllers(position, i);
			position++;
		}
	}

	return;
}
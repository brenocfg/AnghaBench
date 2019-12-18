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
 int PicoAutoRgnOrder ; 
 int PicoRegionOverride ; 

__attribute__((used)) static void region_prevnext(int right)
{
	// jp_ntsc=1, jp_pal=2, usa=4, eu=8
	static int rgn_orders[] = { 0x148, 0x184, 0x814, 0x418, 0x841, 0x481 };
	int i;
	if (right) {
		if (!PicoRegionOverride) {
			for (i = 0; i < 6; i++)
				if (rgn_orders[i] == PicoAutoRgnOrder) break;
			if (i < 5) PicoAutoRgnOrder = rgn_orders[i+1];
			else PicoRegionOverride=1;
		}
		else PicoRegionOverride<<=1;
		if (PicoRegionOverride > 8) PicoRegionOverride = 8;
	} else {
		if (!PicoRegionOverride) {
			for (i = 0; i < 6; i++)
				if (rgn_orders[i] == PicoAutoRgnOrder) break;
			if (i > 0) PicoAutoRgnOrder = rgn_orders[i-1];
		}
		else PicoRegionOverride>>=1;
	}
}
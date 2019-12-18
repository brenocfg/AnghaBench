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
typedef  int u8 ;

/* Variables and functions */
 int WLAN_EID_EXT_SUPP_RATES ; 
 int WLAN_EID_SUPP_RATES ; 

__attribute__((used)) static int prism_build_supp_rates(u8 *buf, const u8 *rates)
{
	int i;

	buf[0] = WLAN_EID_SUPP_RATES;
	for (i = 0; i < 8; i++) {
		/* NULL terminated */
		if (rates[i] == 0x0)
			break;
		buf[i + 2] = rates[i];
	}
	buf[1] = i;

	/* We might still have another 2 rates, which need to go in
	 * extended supported rates */
	if (i == 8 && rates[i] > 0) {
		buf[10] = WLAN_EID_EXT_SUPP_RATES;
		for (; i < 10; i++) {
			/* NULL terminated */
			if (rates[i] == 0x0)
				break;
			buf[i + 2] = rates[i];
		}
		buf[11] = i - 8;
	}

	return (i < 8) ? i + 2 : i + 4;
}
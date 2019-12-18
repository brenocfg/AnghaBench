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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int lbs_data_rate_to_fw_index (int) ; 

__attribute__((used)) static __le16 lbs_rate_to_fw_bitmap(int rate, int lower_rates_ok)
{
/*		Bit  	Rate
*		15:13 Reserved
*		12    54 Mbps
*		11    48 Mbps
*		10    36 Mbps
*		9     24 Mbps
*		8     18 Mbps
*		7     12 Mbps
*		6     9 Mbps
*		5     6 Mbps
*		4     Reserved
*		3     11 Mbps
*		2     5.5 Mbps
*		1     2 Mbps
*		0     1 Mbps
**/

	uint16_t ratemask;
	int i = lbs_data_rate_to_fw_index(rate);
	if (lower_rates_ok)
		ratemask = (0x1fef >> (12 - i));
	else
		ratemask = (1 << i);
	return cpu_to_le16(ratemask);
}
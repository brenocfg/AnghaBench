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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int memcmp (scalar_t__*,scalar_t__*,scalar_t__) ; 

int lbs_ssid_cmp(uint8_t *ssid1, uint8_t ssid1_len, uint8_t *ssid2,
		 uint8_t ssid2_len)
{
	if (ssid1_len != ssid2_len)
		return -1;

	return memcmp(ssid1, ssid2, ssid1_len);
}
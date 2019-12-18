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
 int DS1305_HR_12 ; 
 int DS1305_HR_PM ; 
 int bin2bcd (int) ; 

__attribute__((used)) static u8 hour2bcd(bool hr12, int hour)
{
	if (hr12) {
		hour++;
		if (hour <= 12)
			return DS1305_HR_12 | bin2bcd(hour);
		hour -= 12;
		return DS1305_HR_12 | DS1305_HR_PM | bin2bcd(hour);
	}
	return bin2bcd(hour);
}
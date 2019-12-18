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
 int SENSORS_LIMIT (int,int,int) ; 

__attribute__((used)) static inline u8 FAN_TO_REG(long rpm, int div)
{
	long rpmdiv;
	if (rpm == 0)
		return 0;
	rpmdiv = SENSORS_LIMIT(rpm, 1, 960000) * div;
	return SENSORS_LIMIT((480000 + rpmdiv / 2) / rpmdiv, 1, 255);
}
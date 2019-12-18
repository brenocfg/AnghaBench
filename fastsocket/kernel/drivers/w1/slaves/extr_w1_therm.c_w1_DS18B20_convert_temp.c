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
typedef  int s16 ;

/* Variables and functions */

__attribute__((used)) static inline int w1_DS18B20_convert_temp(u8 rom[9])
{
	int t = ((s16)rom[1] << 8) | rom[0];
	t = t*1000/16;
	return t;
}
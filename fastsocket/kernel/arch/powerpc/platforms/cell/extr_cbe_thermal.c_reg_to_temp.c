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
 int TEMP_MIN ; 

__attribute__((used)) static inline u8 reg_to_temp(u8 reg_value)
{
	return ((reg_value & 0x3f) << 1) + TEMP_MIN;
}
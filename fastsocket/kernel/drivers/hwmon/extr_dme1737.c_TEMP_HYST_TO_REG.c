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
 int SENSORS_LIMIT (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int TEMP_HYST_TO_REG(int val, int ix, int reg)
{
	int hyst = SENSORS_LIMIT((val + 500) / 1000, 0, 15);

	return (ix == 1) ? (reg & 0xf0) | hyst : (reg & 0x0f) | (hyst << 4);
}
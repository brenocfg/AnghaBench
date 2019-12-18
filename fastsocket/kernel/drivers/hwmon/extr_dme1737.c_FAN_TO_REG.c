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

__attribute__((used)) static inline int FAN_TO_REG(int val, int tpc)
{
	if (tpc) {
		return SENSORS_LIMIT(val / tpc, 0, 0xffff);
	} else {
		return (val <= 0) ? 0xffff :
			SENSORS_LIMIT(90000 * 60 / val, 0, 0xfffe);
	}
}
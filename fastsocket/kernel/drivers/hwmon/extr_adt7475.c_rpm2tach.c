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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  SENSORS_LIMIT (int,int,int) ; 

__attribute__((used)) static inline u16 rpm2tach(unsigned long rpm)
{
	if (rpm == 0)
		return 0;

	return SENSORS_LIMIT((90000 * 60) / rpm, 1, 0xFFFF);
}
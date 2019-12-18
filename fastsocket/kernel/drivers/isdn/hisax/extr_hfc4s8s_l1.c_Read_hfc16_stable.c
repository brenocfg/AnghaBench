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
typedef  int /*<<< orphan*/  hfc4s8s_hw ;

/* Variables and functions */
 int Read_hfc16 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
Read_hfc16_stable(hfc4s8s_hw * hw, int reg)
{
	int ref16;
	int in16;

	ref16 = Read_hfc16(hw, reg);
	while (((in16 = Read_hfc16(hw, reg)) != ref16)) {
		ref16 = in16;
	}
	return in16;
}
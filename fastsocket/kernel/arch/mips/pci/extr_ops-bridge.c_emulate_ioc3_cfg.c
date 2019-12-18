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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static u32 emulate_ioc3_cfg(int where, int size)
{
	if (size == 1 && where == 0x3d)
		return 0x01;
	else if (size == 2 && where == 0x3c)
		return 0x0100;
	else if (size == 4 && where == 0x3c)
		return 0x00000100;

	return 0;
}
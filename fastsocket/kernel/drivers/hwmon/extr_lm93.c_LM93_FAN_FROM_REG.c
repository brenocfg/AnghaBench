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
typedef  int u16 ;

/* Variables and functions */
 int le16_to_cpu (int) ; 

__attribute__((used)) static int LM93_FAN_FROM_REG(u16 regs)
{
	const u16 count = le16_to_cpu(regs) >> 2;
	return count==0 ? -1 : count==0x3fff ? 0: 1350000 / count;
}
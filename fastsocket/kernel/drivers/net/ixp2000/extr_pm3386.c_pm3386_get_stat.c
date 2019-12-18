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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 int pm3386_port_reg_read (int,scalar_t__,int) ; 

__attribute__((used)) static u32 pm3386_get_stat(int port, u16 base)
{
	u32 value;

	value = pm3386_port_reg_read(port, base, 0x100);
	value |= pm3386_port_reg_read(port, base + 1, 0x100) << 16;

	return value;
}
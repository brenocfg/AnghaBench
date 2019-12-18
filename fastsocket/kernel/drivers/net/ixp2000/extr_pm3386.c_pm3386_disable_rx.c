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
 int pm3386_port_reg_read (int,int,int) ; 
 int /*<<< orphan*/  pm3386_port_reg_write (int,int,int,int) ; 

void pm3386_disable_rx(int port)
{
	u16 temp;

	temp = pm3386_port_reg_read(port, 0x303, 0x100);
	temp &= 0xefff;
	pm3386_port_reg_write(port, 0x303, 0x100, temp);
}
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
 int /*<<< orphan*/  CALEB_PORTEN ; 
 int caleb_reg_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caleb_reg_write (int /*<<< orphan*/ ,int) ; 

void caleb_enable_rx(int port)
{
	u8 temp;

	temp = caleb_reg_read(CALEB_PORTEN);
	temp |= 1 << port;
	caleb_reg_write(CALEB_PORTEN, temp);
}
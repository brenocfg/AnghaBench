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
struct sh_mobile_lcdc_sys_bus_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdelay (int) ; 
 int read_reg (void*,struct sh_mobile_lcdc_sys_bus_ops*) ; 
 int /*<<< orphan*/  write_reg (void*,struct sh_mobile_lcdc_sys_bus_ops*,int,int) ; 

__attribute__((used)) static unsigned long read_device_code(void *sohandle,
				      struct sh_mobile_lcdc_sys_bus_ops *so)
{
	unsigned long device_code;

	/* access protect OFF */
	write_reg(sohandle, so, 0, 0xb0);
	write_reg(sohandle, so, 1, 0x00);

	/* deep standby OFF */
	write_reg(sohandle, so, 0, 0xb1);
	write_reg(sohandle, so, 1, 0x00);

	/* device code command */
	write_reg(sohandle, so, 0, 0xbf);
	mdelay(50);

	/* dummy read */
	read_reg(sohandle, so);

	/* read device code */
	device_code = ((read_reg(sohandle, so) & 0xff) << 24);
	device_code |= ((read_reg(sohandle, so) & 0xff) << 16);
	device_code |= ((read_reg(sohandle, so) & 0xff) << 8);
	device_code |= (read_reg(sohandle, so) & 0xff);

	return device_code;
}
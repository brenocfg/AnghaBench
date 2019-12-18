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
 int /*<<< orphan*/  write_memory_start (void*,struct sh_mobile_lcdc_sys_bus_ops*) ; 
 int /*<<< orphan*/  write_reg (void*,struct sh_mobile_lcdc_sys_bus_ops*,int,int) ; 

__attribute__((used)) static void clear_memory(void *sohandle,
			 struct sh_mobile_lcdc_sys_bus_ops *so)
{
	int i;

	/* write start */
	write_memory_start(sohandle, so);

	/* paint it black */
	for (i = 0; i < (240 * 400); i++)
		write_reg(sohandle, so, 1, 0x00);
}
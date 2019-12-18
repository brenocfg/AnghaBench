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
 int /*<<< orphan*/  h3600_irda_data ; 
 int /*<<< orphan*/  h3xxx_flash_data ; 
 int /*<<< orphan*/  h3xxx_flash_resource ; 
 int /*<<< orphan*/  sa11x0_set_flash_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sa11x0_set_irda_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void h3xxx_mach_init(void)
{
	sa11x0_set_flash_data(&h3xxx_flash_data, &h3xxx_flash_resource, 1);
	sa11x0_set_irda_data(&h3600_irda_data);
}
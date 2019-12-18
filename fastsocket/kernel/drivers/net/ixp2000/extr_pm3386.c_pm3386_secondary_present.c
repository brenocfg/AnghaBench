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
 int pm3386_reg_read (int,int /*<<< orphan*/ ) ; 

int pm3386_secondary_present(void)
{
	return pm3386_reg_read(1, 0) == 0x3386;
}
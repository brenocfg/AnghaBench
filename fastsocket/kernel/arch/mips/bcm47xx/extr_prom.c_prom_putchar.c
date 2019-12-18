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
 int /*<<< orphan*/  cfe_cons_handle ; 
 scalar_t__ cfe_write (int /*<<< orphan*/ ,char*,int) ; 

void prom_putchar(char c)
{
	while (cfe_write(cfe_cons_handle, &c, 1) == 0)
		;
}
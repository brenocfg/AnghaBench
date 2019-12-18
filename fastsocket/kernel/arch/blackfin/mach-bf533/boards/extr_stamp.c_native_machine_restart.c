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
 int /*<<< orphan*/  PF0 ; 
 int /*<<< orphan*/  bfin_write_FIO_DIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_FIO_FLAG_C (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_FIO_INEN (int /*<<< orphan*/ ) ; 

void native_machine_restart(char *cmd)
{
	/* workaround pull up on cpld / flash pin not being strong enough */
	bfin_write_FIO_INEN(~PF0);
	bfin_write_FIO_DIR(PF0);
	bfin_write_FIO_FLAG_C(PF0);
}
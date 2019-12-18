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
struct at91_ide_info {int /*<<< orphan*/  mode; int /*<<< orphan*/  cs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_SMC_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_sys_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_smc_mode(struct at91_ide_info *info)
{
	at91_sys_write(AT91_SMC_MODE(info->cs), info->mode);
	return;
}
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
 int /*<<< orphan*/  DA850_MMCSD_CD_PIN ; 
 int /*<<< orphan*/  gpio_get_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da850_evm_mmc_get_cd(int index)
{
	return !gpio_get_value(DA850_MMCSD_CD_PIN);
}
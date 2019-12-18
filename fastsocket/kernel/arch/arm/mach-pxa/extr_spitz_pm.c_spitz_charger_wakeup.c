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
 unsigned long GPIO_bit (int /*<<< orphan*/ ) ; 
 unsigned long GPLR0 ; 
 int /*<<< orphan*/  SPITZ_GPIO_KEY_INT ; 
 int /*<<< orphan*/  SPITZ_GPIO_SYNC ; 

__attribute__((used)) static unsigned long spitz_charger_wakeup(void)
{
	return (~GPLR0 & GPIO_bit(SPITZ_GPIO_KEY_INT)) | (GPLR0 & GPIO_bit(SPITZ_GPIO_SYNC));
}
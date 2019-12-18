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
typedef  int /*<<< orphan*/  ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  cmd64x_tune_pio (int /*<<< orphan*/ *,int const) ; 

__attribute__((used)) static void cmd64x_set_pio_mode(ide_drive_t *drive, const u8 pio)
{
	/*
	 * Filter out the prefetch control values
	 * to prevent PIO5 from being programmed
	 */
	if (pio == 8 || pio == 9)
		return;

	cmd64x_tune_pio(drive, pio);
}
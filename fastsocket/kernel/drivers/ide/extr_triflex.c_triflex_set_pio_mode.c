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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  ide_drive_t ;

/* Variables and functions */
 scalar_t__ const XFER_PIO_0 ; 
 int /*<<< orphan*/  triflex_set_mode (int /*<<< orphan*/ *,scalar_t__ const) ; 

__attribute__((used)) static void triflex_set_pio_mode(ide_drive_t *drive, const u8 pio)
{
	triflex_set_mode(drive, XFER_PIO_0 + pio);
}
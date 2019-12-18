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
typedef  int /*<<< orphan*/  ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  hpt370_clear_engine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ide_dma_start (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hpt370_dma_start(ide_drive_t *drive)
{
#ifdef HPT_RESET_STATE_ENGINE
	hpt370_clear_engine(drive);
#endif
	ide_dma_start(drive);
}
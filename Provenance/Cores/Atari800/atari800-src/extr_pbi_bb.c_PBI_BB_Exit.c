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
 int /*<<< orphan*/ * PBI_SCSI_disk ; 
 int /*<<< orphan*/ * bb_ram ; 
 int /*<<< orphan*/ * bb_rom ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void PBI_BB_Exit(void)
{
	if (PBI_SCSI_disk != NULL) {
		fclose(PBI_SCSI_disk);
		PBI_SCSI_disk = NULL;
	}
	free(bb_ram);
	free(bb_rom);
	bb_rom = bb_ram = NULL;
}
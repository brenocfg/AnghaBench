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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Util_filenamenotset (char*) ; 
 char* bb_rom_filename ; 
 char* bb_scsi_disk_filename ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 

void PBI_BB_WriteConfig(FILE *fp)
{
	fprintf(fp, "BLACK_BOX_ROM=%s\n", bb_rom_filename);
	if (!Util_filenamenotset(bb_scsi_disk_filename)) {
		fprintf(fp, "BB_SCSI_DISK=%s\n", bb_scsi_disk_filename);
	}
}
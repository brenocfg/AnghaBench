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
 int /*<<< orphan*/  D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PBI_SCSI_disk ; 
 scalar_t__ SCSI_PHASE_COMMAND ; 
 scalar_t__ SCSI_PHASE_DATAIN ; 
 scalar_t__ SCSI_PHASE_DATAOUT ; 
 scalar_t__ SCSI_PHASE_MSGIN ; 
 scalar_t__ SCSI_PHASE_SELECTION ; 
 scalar_t__ SCSI_PHASE_STATUS ; 
 int /*<<< orphan*/  fwrite (int*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int* scsi_buffer ; 
 int scsi_bufpos ; 
 int scsi_byte ; 
 int /*<<< orphan*/  scsi_changephase (scalar_t__) ; 
 int scsi_count ; 
 scalar_t__ scsi_phase ; 
 int /*<<< orphan*/  scsi_process_command () ; 

__attribute__((used)) static void scsi_nextbyte(void)
{
	if (scsi_phase == SCSI_PHASE_DATAIN) {
		scsi_bufpos++;
		if (scsi_bufpos >= scsi_count) {
			scsi_changephase(SCSI_PHASE_STATUS);
			scsi_buffer[0] = 0;
		}
	}
	else if (scsi_phase == SCSI_PHASE_STATUS) {
		D(printf("SCSI status\n"));
		scsi_changephase(SCSI_PHASE_MSGIN);
		scsi_buffer[0] = 0;
	}
	else if (scsi_phase == SCSI_PHASE_MSGIN) {
		D(printf("SCSI msg\n"));
		scsi_changephase(SCSI_PHASE_SELECTION);
	}
	else if (scsi_phase == SCSI_PHASE_COMMAND) {
		scsi_buffer[scsi_bufpos++] = scsi_byte;
		if (scsi_bufpos >= 0x06) {
			scsi_process_command();
			scsi_bufpos = 0;
		}
	}
	else if (scsi_phase == SCSI_PHASE_DATAOUT) {
		D(printf("SCSI data out:%2x\n", scsi_byte));
		scsi_buffer[scsi_bufpos++] = scsi_byte;
		if (scsi_bufpos >= scsi_count) {
			fwrite(scsi_buffer, 1, 256, PBI_SCSI_disk);
			scsi_changephase(SCSI_PHASE_STATUS);
			scsi_buffer[0] = 0;
		}
	}
}
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
 void* FALSE ; 
 void* PBI_SCSI_BSY ; 
 void* PBI_SCSI_CD ; 
 void* PBI_SCSI_IO ; 
 void* PBI_SCSI_MSG ; 
 void* PBI_SCSI_REQ ; 
#define  SCSI_PHASE_COMMAND 133 
#define  SCSI_PHASE_DATAIN 132 
#define  SCSI_PHASE_DATAOUT 131 
#define  SCSI_PHASE_MSGIN 130 
#define  SCSI_PHASE_SELECTION 129 
#define  SCSI_PHASE_STATUS 128 
 void* TRUE ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 scalar_t__ scsi_bufpos ; 
 int scsi_phase ; 

__attribute__((used)) static void scsi_changephase(int phase)
{
	D(printf("scsi_changephase:%d\n",phase));
	switch(phase) {
		case SCSI_PHASE_SELECTION:
				PBI_SCSI_REQ = FALSE;
				PBI_SCSI_BSY = FALSE;
				PBI_SCSI_CD = FALSE;
				PBI_SCSI_IO = FALSE;
				PBI_SCSI_MSG = FALSE;
				break;
		case SCSI_PHASE_DATAOUT:
				PBI_SCSI_REQ = TRUE;
				PBI_SCSI_BSY = TRUE;
				PBI_SCSI_CD = FALSE;
				PBI_SCSI_IO = FALSE;
				PBI_SCSI_MSG = FALSE;
				break;
		case SCSI_PHASE_DATAIN:
				PBI_SCSI_REQ = TRUE;
				PBI_SCSI_BSY = TRUE;
				PBI_SCSI_CD = FALSE;
				PBI_SCSI_IO = TRUE;
				PBI_SCSI_MSG = FALSE;
				break;
		case SCSI_PHASE_COMMAND:
				PBI_SCSI_REQ = TRUE;
				PBI_SCSI_BSY = TRUE;
				PBI_SCSI_CD = TRUE;
				PBI_SCSI_IO = FALSE;
				PBI_SCSI_MSG = FALSE;
				break;
		case SCSI_PHASE_STATUS:
				PBI_SCSI_REQ = TRUE;
				PBI_SCSI_BSY = TRUE;
				PBI_SCSI_CD = TRUE;
				PBI_SCSI_IO = TRUE;
				PBI_SCSI_MSG = FALSE;
				break;
		case SCSI_PHASE_MSGIN:
				PBI_SCSI_REQ = TRUE;
				PBI_SCSI_BSY = TRUE;
				PBI_SCSI_CD = TRUE;
				PBI_SCSI_IO = FALSE;
				PBI_SCSI_MSG = TRUE;
				break;
	}
	scsi_bufpos = 0;
	scsi_phase = phase;
}
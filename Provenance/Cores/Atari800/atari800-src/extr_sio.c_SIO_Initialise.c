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
 int SIO_MAX_DRIVES ; 
 int /*<<< orphan*/  SIO_NoFrame ; 
 int /*<<< orphan*/  SIO_OFF ; 
 int /*<<< orphan*/ * SIO_drive_status ; 
 int /*<<< orphan*/ * SIO_filename ; 
 int* SIO_format_sectorcount ; 
 int* SIO_format_sectorsize ; 
 int TRUE ; 
 int /*<<< orphan*/  TransferStatus ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

int SIO_Initialise(int *argc, char *argv[])
{
	int i;
	for (i = 0; i < SIO_MAX_DRIVES; i++) {
		strcpy(SIO_filename[i], "Off");
		SIO_drive_status[i] = SIO_OFF;
		SIO_format_sectorsize[i] = 128;
		SIO_format_sectorcount[i] = 720;
	}
	TransferStatus = SIO_NoFrame;

	return TRUE;
}
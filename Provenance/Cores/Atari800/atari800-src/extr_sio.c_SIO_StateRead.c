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
typedef  scalar_t__ SIO_UnitStatus ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int FILENAME_MAX ; 
 int /*<<< orphan*/  SIO_Mount (int,char*,int /*<<< orphan*/ ) ; 
#define  SIO_READ_ONLY 129 
#define  SIO_READ_WRITE 128 
 scalar_t__* SIO_drive_status ; 
 int /*<<< orphan*/  StateSav_ReadFNAME (char*) ; 
 int /*<<< orphan*/  StateSav_ReadINT (int*,int) ; 
 int /*<<< orphan*/  TRUE ; 

void SIO_StateRead(void)
{
	int i;

	for (i = 0; i < 8; i++) {
		int saved_drive_status;
		char filename[FILENAME_MAX];

		StateSav_ReadINT(&saved_drive_status, 1);
		SIO_drive_status[i] = (SIO_UnitStatus)saved_drive_status;

		StateSav_ReadFNAME(filename);
		if (filename[0] == 0)
			continue;

		/* If the disk drive wasn't empty or off when saved,
		   mount the disk */
		switch (saved_drive_status) {
		case SIO_READ_ONLY:
			SIO_Mount(i + 1, filename, TRUE);
			break;
		case SIO_READ_WRITE:
			SIO_Mount(i + 1, filename, FALSE);
			break;
		default:
			break;
		}
	}
}
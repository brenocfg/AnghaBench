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
 int /*<<< orphan*/ * SIO_drive_status ; 
 int /*<<< orphan*/ * SIO_filename ; 
 int /*<<< orphan*/  StateSav_SaveFNAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StateSav_SaveINT (int*,int) ; 

void SIO_StateSave(void)
{
	int i;

	for (i = 0; i < 8; i++) {
		StateSav_SaveINT((int *) &SIO_drive_status[i], 1);
		StateSav_SaveFNAME(SIO_filename[i]);
	}
}
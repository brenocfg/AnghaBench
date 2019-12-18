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
 int /*<<< orphan*/  SIO_Dismount (int) ; 
 int /*<<< orphan*/  SIO_OFF ; 
 int /*<<< orphan*/ * SIO_drive_status ; 
 int /*<<< orphan*/ * SIO_filename ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

void SIO_DisableDrive(int diskno)
{
	SIO_Dismount(diskno);
	SIO_drive_status[diskno - 1] = SIO_OFF;
	strcpy(SIO_filename[diskno - 1], "Off");
}
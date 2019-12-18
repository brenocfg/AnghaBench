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
 scalar_t__ CASSETTE_STATUS_READ_WRITE ; 
 scalar_t__ CASSETTE_status ; 
 int CASSETTE_write_protect ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  UpdateFlags () ; 

int CASSETTE_ToggleWriteProtect(void)
{
	if (CASSETTE_status != CASSETTE_STATUS_READ_WRITE)
		return FALSE;
	CASSETTE_write_protect = !CASSETTE_write_protect;
	UpdateFlags();
	return TRUE;
}
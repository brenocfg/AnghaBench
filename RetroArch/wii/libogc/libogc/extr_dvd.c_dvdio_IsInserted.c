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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  DVD_LowGetStatus (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ DVD_STATUS (int /*<<< orphan*/ ) ; 
 scalar_t__ DVD_STATUS_READY ; 

__attribute__((used)) static bool dvdio_IsInserted()
{
	u32 status = 0;
	DVD_LowGetStatus(&status, NULL);

	if(DVD_STATUS(status) == DVD_STATUS_READY)
		return true;

	return false;
}
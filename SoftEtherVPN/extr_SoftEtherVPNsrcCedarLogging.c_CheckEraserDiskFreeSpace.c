#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
struct TYPE_3__ {scalar_t__ MinFreeSpace; int /*<<< orphan*/  DirName; } ;
typedef  TYPE_1__ ERASER ;

/* Variables and functions */
 int GetDiskFree (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool CheckEraserDiskFreeSpace(ERASER *e)
{
	UINT64 s;
	// Validate arguments
	if (e == NULL)
	{
		return true;
	}

	// Get the free disk space
	if (GetDiskFree(e->DirName, &s, NULL, NULL) == false)
	{
		// Acquisition failure
		return true;
	}

	if (e->MinFreeSpace > s)
	{
		// The free space is smaller than specified bytes
		return false;
	}

	// Vacant enough
	return true;
}
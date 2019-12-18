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
typedef  int /*<<< orphan*/  ResourceOwner ;
typedef  int /*<<< orphan*/  JobDirectoryEntry ;

/* Variables and functions */
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MultiResourceOwnerReleaseCallback ; 
 int NumAllocatedJobDirectories ; 
 int NumRegisteredJobDirectories ; 
 int /*<<< orphan*/  RegisterResourceReleaseCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RegisteredJobDirectories ; 
 int RegisteredResownerCallback ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 scalar_t__ repalloc (int /*<<< orphan*/ *,int) ; 

void
ResourceOwnerEnlargeJobDirectories(ResourceOwner owner)
{
	int newMax = 0;

	/* ensure callback is registered */
	if (!RegisteredResownerCallback)
	{
		RegisterResourceReleaseCallback(MultiResourceOwnerReleaseCallback, NULL);
		RegisteredResownerCallback = true;
	}

	if (RegisteredJobDirectories == NULL)
	{
		newMax = 16;
		RegisteredJobDirectories =
			(JobDirectoryEntry *) MemoryContextAlloc(TopMemoryContext,
													 newMax * sizeof(JobDirectoryEntry));
		NumAllocatedJobDirectories = newMax;
	}
	else if (NumRegisteredJobDirectories + 1 > NumAllocatedJobDirectories)
	{
		newMax = NumAllocatedJobDirectories * 2;
		RegisteredJobDirectories =
			(JobDirectoryEntry *) repalloc(RegisteredJobDirectories,
										   newMax * sizeof(JobDirectoryEntry));
		NumAllocatedJobDirectories = newMax;
	}
}
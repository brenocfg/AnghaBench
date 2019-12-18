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
struct TYPE_3__ {scalar_t__ owner; int /*<<< orphan*/  jobId; } ;
typedef  scalar_t__ ResourceReleasePhase ;
typedef  TYPE_1__ JobDirectoryEntry ;

/* Variables and functions */
 scalar_t__ CurrentResourceOwner ; 
 int NumRegisteredJobDirectories ; 
 scalar_t__ RESOURCE_RELEASE_AFTER_LOCKS ; 
 TYPE_1__* RegisteredJobDirectories ; 
 int /*<<< orphan*/  RemoveJobDirectory (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
MultiResourceOwnerReleaseCallback(ResourceReleasePhase phase,
								  bool isCommit,
								  bool isTopLevel,
								  void *arg)
{
	int lastJobIndex = NumRegisteredJobDirectories - 1;
	int jobIndex = 0;

	if (phase == RESOURCE_RELEASE_AFTER_LOCKS)
	{
		/*
		 * Remove all remaining job directories, after locks have been
		 * released.
		 */
		for (jobIndex = lastJobIndex; jobIndex >= 0; jobIndex--)
		{
			JobDirectoryEntry *entry = &RegisteredJobDirectories[jobIndex];

			if (entry->owner == CurrentResourceOwner)
			{
				RemoveJobDirectory(entry->jobId);
			}
		}
	}
}
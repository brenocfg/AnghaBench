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
typedef  int /*<<< orphan*/  uint64 ;
struct TYPE_3__ {int /*<<< orphan*/  jobId; int /*<<< orphan*/  owner; } ;
typedef  int /*<<< orphan*/  ResourceOwner ;
typedef  TYPE_1__ JobDirectoryEntry ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int NumAllocatedJobDirectories ; 
 int NumRegisteredJobDirectories ; 
 TYPE_1__* RegisteredJobDirectories ; 

void
ResourceOwnerRememberJobDirectory(ResourceOwner owner, uint64 jobId)
{
	JobDirectoryEntry *entry = NULL;

	Assert(NumRegisteredJobDirectories + 1 <= NumAllocatedJobDirectories);
	entry = &RegisteredJobDirectories[NumRegisteredJobDirectories];
	entry->owner = owner;
	entry->jobId = jobId;
	NumRegisteredJobDirectories++;
}
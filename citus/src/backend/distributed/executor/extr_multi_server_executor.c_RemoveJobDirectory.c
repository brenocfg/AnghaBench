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
typedef  int /*<<< orphan*/  uint64 ;
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  CitusRemoveDirectory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CurrentResourceOwner ; 
 int /*<<< orphan*/  MasterJobDirectoryName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResourceOwnerForgetJobDirectory (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
RemoveJobDirectory(uint64 jobId)
{
	StringInfo jobDirectoryName = MasterJobDirectoryName(jobId);
	CitusRemoveDirectory(jobDirectoryName);

	ResourceOwnerForgetJobDirectory(CurrentResourceOwner, jobId);
}
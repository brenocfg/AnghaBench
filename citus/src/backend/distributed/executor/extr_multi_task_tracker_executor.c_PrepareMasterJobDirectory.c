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
struct TYPE_3__ {int /*<<< orphan*/  jobId; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ Job ;

/* Variables and functions */
 int /*<<< orphan*/  CitusCreateDirectory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CurrentResourceOwner ; 
 int /*<<< orphan*/  MasterJobDirectoryName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResourceOwnerEnlargeJobDirectories (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResourceOwnerRememberJobDirectory (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
PrepareMasterJobDirectory(Job *workerJob)
{
	StringInfo jobDirectoryName = MasterJobDirectoryName(workerJob->jobId);
	CitusCreateDirectory(jobDirectoryName);

	ResourceOwnerEnlargeJobDirectories(CurrentResourceOwner);
	ResourceOwnerRememberJobDirectory(CurrentResourceOwner, workerJob->jobId);
}
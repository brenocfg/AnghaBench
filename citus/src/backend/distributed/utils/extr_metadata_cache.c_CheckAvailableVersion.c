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
 char* AvailableExtensionVersion () ; 
 int /*<<< orphan*/  CITUS_EXTENSIONVERSION ; 
 int /*<<< orphan*/  CITUS_MAJORVERSION ; 
 int /*<<< orphan*/  EnableVersionChecks ; 
 int /*<<< orphan*/  MajorVersionsCompatible (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

bool
CheckAvailableVersion(int elevel)
{
	char *availableVersion = NULL;

	if (!EnableVersionChecks)
	{
		return true;
	}

	availableVersion = AvailableExtensionVersion();

	if (!MajorVersionsCompatible(availableVersion, CITUS_EXTENSIONVERSION))
	{
		ereport(elevel, (errmsg("loaded Citus library version differs from latest "
								"available extension version"),
						 errdetail("Loaded library requires %s, but the latest control "
								   "file specifies %s.", CITUS_MAJORVERSION,
								   availableVersion),
						 errhint("Restart the database to load the latest Citus "
								 "library.")));
		return false;
	}

	return true;
}
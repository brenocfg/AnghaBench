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
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CITUS_EXTENSIONVERSION ; 
 int /*<<< orphan*/  CITUS_MAJORVERSION ; 
 int /*<<< orphan*/  CitusHasBeenLoaded () ; 
 int /*<<< orphan*/  EnableVersionChecks ; 
 char* InstalledExtensionVersion () ; 
 int /*<<< orphan*/  MajorVersionsCompatible (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

__attribute__((used)) static bool
CheckInstalledVersion(int elevel)
{
	char *installedVersion = NULL;

	Assert(CitusHasBeenLoaded());
	Assert(EnableVersionChecks);

	installedVersion = InstalledExtensionVersion();

	if (!MajorVersionsCompatible(installedVersion, CITUS_EXTENSIONVERSION))
	{
		ereport(elevel, (errmsg("loaded Citus library version differs from installed "
								"extension version"),
						 errdetail("Loaded library requires %s, but the installed "
								   "extension version is %s.", CITUS_MAJORVERSION,
								   installedVersion),
						 errhint("Run ALTER EXTENSION citus UPDATE and try again.")));
		return false;
	}

	return true;
}
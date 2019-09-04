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
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 int /*<<< orphan*/  CEDAR_VERSION_BUILD ; 
 int /*<<< orphan*/  CEDAR_VERSION_MAJOR ; 
 int /*<<< orphan*/  CEDAR_VERSION_MINOR ; 
 int /*<<< orphan*/  Format (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void GetCedarVersion(char *tmp, UINT size)
{
	// Validate arguments
	if (tmp == NULL)
	{
		return;
	}

	Format(tmp, size, "%u.%02u.%u", CEDAR_VERSION_MAJOR, CEDAR_VERSION_MINOR, CEDAR_VERSION_BUILD);
}